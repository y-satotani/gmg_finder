
#include "initial_builder_stree_conjecture.hpp"

namespace ccheck {

  vertex_t
  initial_builder_stree_conjecture::parent_of(graph_config* c, vertex_t v) {
    if(v == 0)
      return -1;
    else if(v <= c->d())
      return 0;
    else {
      std::size_t depth = tree_depth(v, c->d());
      std::size_t n_vert_layer =
        n_vert_btree(depth-1, c->d()) - n_vert_btree(depth-2, c->d());
      return (v-n_vert_btree(depth-1, c->d())) % (n_vert_layer) +
        n_vert_btree(depth-2, c->d());
    }
  }

  std::vector<vertex_t>
  initial_builder_stree_conjecture::initial_vertices(graph_config* c) {
    std::vector<vertex_t> t_verts;
    for(vertex_t v = 0; v < c->n(); v++)
      t_verts.push_back(v);
    return t_verts;
  }

  std::vector<vertex_t>
  initial_builder_stree_conjecture::possible_vertices(graph_config* c) {
    unsigned int degree[c->n()];
    for(vertex_t v = 0; v < c->n(); v++)
      degree[v] = 0;
    std::vector<edge_t> t_edges = initial_edges(c);
    for(std::size_t ei = 0; ei < t_edges.size(); ei++) {
      degree[t_edges[ei].first]++;
      degree[t_edges[ei].second]++;
    }

    std::vector<vertex_t> l_verts;
    for(vertex_t v = 0; v < c->n(); v++)
      if(degree[v] < c->d())
        l_verts.push_back(v);
    return l_verts;
  }

  std::vector<edge_t>
  initial_builder_stree_conjecture::initial_edges(graph_config* c) {
    std::vector<edge_t> t_edges;
    for(vertex_t v = 1; v < c->n(); v++)
      t_edges.push_back(edge_t(parent_of(c, v), v));
    return t_edges;
  }

  std::vector<edge_t>
  initial_builder_stree_conjecture::possible_edges(graph_config* c) {
    std::vector<vertex_t> l_verts = possible_vertices(c);
    std::vector<edge_t> l_edges;
    for(std::size_t i = 0; i < l_verts.size(); i++)
      for(std::size_t j = 0; j < l_verts.size(); j++)
        if(i < j && parent_of(c, l_verts[j]) != l_verts[i])
          l_edges.push_back(edge_t(l_verts[i], l_verts[j]));
    return l_edges;
  }

}
