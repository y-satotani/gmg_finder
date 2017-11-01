
#include "initial_builder.hpp"
#include <cmath>

namespace gmgf {

  vertex_t initial_builder::parent_of(graph_config* c, vertex_t v) {
    if(v == 0)
      return -1;
    else if(v <= c->d())
      return 0;
    else {
      unsigned int depth = tree_depth(v, c->d());
      return (v-n_vert_btree(depth-1, c->d())) / (c->d()-1) +
        n_vert_btree(depth-2, c->d());
    }
  }

  std::vector<vertex_t>
  initial_builder::initial_vertices(graph_config* c) {
    std::vector<vertex_t> t_verts;
    for(vertex_t v = 0; v < n_vert_btree(c->Q(), c->d()); v++)
      t_verts.push_back(v);
    return t_verts;
  }

  std::vector<vertex_t>
  initial_builder::possible_vertices(graph_config* c) {
    std::vector<vertex_t> leaves;
    for(vertex_t v = n_vert_btree(c->Q() - 1, c->d());
        v < c->n(); v++)
      leaves.push_back(v);
    return leaves;
  }

  std::vector<edge_t>
  initial_builder::initial_edges(graph_config* c) {
    std::vector<edge_t> t_edges;
    std::vector<vertex_t> t_verts = initial_vertices(c);
    for(std::size_t i = 0; i < t_verts.size(); i++)
      if(t_verts[i] > 0)
        t_edges.push_back(edge_t(parent_of(c, t_verts[i]), t_verts[i]));
    return t_edges;
  }

  std::vector<edge_t>
  initial_builder::possible_edges(graph_config* c) {
    std::vector<edge_t> l_edges;
    std::vector<vertex_t> leaves = possible_vertices(c);
    for(std::size_t i = 0; i < leaves.size(); i++)
      for(std::size_t j = 0; j < leaves.size(); j++)
        if(i < j)
          l_edges.push_back(edge_t(leaves[i], leaves[j]));
    return l_edges;
  }

  std::vector<std::pair<std::size_t, std::size_t> >
  initial_builder::vertex_frontier(graph_config* c) {
    std::vector<std::pair<std::size_t, std::size_t> > frontier;
    std::vector<edge_t> l_edges = possible_edges(c);
    for(size_t vi = 0; vi < c->n(); vi++) {
      std::pair<int, int> p(-1, -1);
      for(size_t ei = 0; ei < l_edges.size(); ei++) {
        if(l_edges[ei].first == vi || l_edges[ei].second == vi) {
          if(p.first < 0) p.first = ei;
          p.second = ei;
        }
      }
      frontier.push_back(p);
    }
    return frontier;
  }

  igraph_t initial_builder::build(graph_config* c) {
    igraph_t graph;
    igraph_empty(&graph, c->n(), IGRAPH_UNDIRECTED);
    std::vector<edge_t> t_edges = initial_edges(c);
    for(std::size_t i = 0; i < t_edges.size(); i++)
      igraph_add_edge(&graph, t_edges[i].first, t_edges[i].second);
    return graph;
  }

}
