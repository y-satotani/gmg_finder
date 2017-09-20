
#include "graph_config.hpp"
#include <cmath>

namespace ccheck {

  graph_config::graph_config(unsigned int n, unsigned int d) {
    _n = n;
    _d = d;
  }

  unsigned int graph_config::n() {
    return _n;
  }

  unsigned int graph_config::d() {
    return _d;
  }

  unsigned int graph_config::Q() {
    unsigned int depth = tree_depth(_n-1, _d);
    if(_n == n_vert_btree(depth, _d))
      return depth;
    else
      return depth - 1;
  }

  unsigned int graph_config::R() {
    return _n - n_vert_btree(Q() - 1, _d);
  }

  vertex_t graph_config::parent_of(vertex_t v) {
    if(v == 0)
      return -1;
    else if(v <= d())
      return 0;
    else {
      unsigned int depth = tree_depth(v, d());
      return (v-n_vert_btree(depth-1, d())) / (d()-1) +
        n_vert_btree(depth-2, d());
    }
  }

  std::vector<vertex_t> graph_config::tree_vertices() {
    std::vector<vertex_t> t_verts;
    for(vertex_t v = 0; v < n_vert_btree(Q(), d()); v++)
      t_verts.push_back(v);
    return t_verts;
  }

  std::vector<edge_t> graph_config::tree_edges() {
    std::vector<edge_t> t_edges;
    std::vector<vertex_t> t_verts = tree_vertices();
    for(std::size_t i = 0; i < t_verts.size(); i++)
      if(t_verts[i] > 0)
        t_edges.push_back(edge_t(t_verts[i], parent_of(t_verts[i])));
    return t_edges;
  }

  std::vector<vertex_t> graph_config::leaf_vertices() {
    std::vector<vertex_t> leaves;
    for(vertex_t v = n() - R(); v < n(); v++)
      leaves.push_back(v);
    return leaves;
  }

  std::vector<edge_t> graph_config::leaf_edges() {
    std::vector<edge_t> l_edges;
    std::vector<vertex_t> leaves = leaf_vertices();
    for(std::size_t i = 0; i < leaves.size(); i++)
      for(std::size_t j = 0; j < leaves.size(); j++)
        if(i < j)
          l_edges.push_back(edge_t(leaves[i], leaves[j]));
    return l_edges;
  }

  igraph_t graph_config::build_tree() {
    igraph_t graph;
    igraph_empty(&graph, _n, IGRAPH_UNDIRECTED);
    std::vector<edge_t> t_edges = tree_edges();
    for(std::size_t i = 0; i < t_edges.size(); i++)
      igraph_add_edge(&graph, t_edges[i].first, t_edges[i].second);
    return graph;
  }

  unsigned int tree_depth(int v, unsigned int d) {
    if(v <= 0)
      return 0;
    else
      return (unsigned int)(log((v-1.)*(d-2.)/d+1) / log(d-1)) + 1;
  }

  unsigned int n_vert_btree(unsigned int dep, unsigned int deg) {
    return (unsigned int)(deg * (pow(deg-1, dep) - 1)) / (deg - 2) + 1;
  }

}
