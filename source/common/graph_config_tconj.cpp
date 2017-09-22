
#include "graph_config_tconj.hpp"

namespace ccheck {

  graph_config_tconj::graph_config_tconj(std::size_t n, std::size_t d)
    : graph_config(n, d) {
  }

  vertex_t graph_config_tconj::parent_of(vertex_t v) {
    if(v == 0)
      return -1;
    else if(v <= d())
      return 0;
    else {
      std::size_t depth = tree_depth(v, d());
      std::size_t n_vert_layer =
        n_vert_btree(depth-1, d()) - n_vert_btree(depth-2, d());
      return (v-n_vert_btree(depth-1, d())) % (n_vert_layer) +
        n_vert_btree(depth-2, d());
    }
  }

  std::vector<vertex_t> graph_config_tconj::tree_vertices() {
    std::vector<vertex_t> t_verts;
    for(vertex_t v = 0; v < n(); v++)
      t_verts.push_back(v);
    return t_verts;
  }

  std::vector<edge_t> graph_config_tconj::tree_edges() {
    std::vector<edge_t> t_edges;
    for(vertex_t v = 1; v < n(); v++)
      t_edges.push_back(edge_t(parent_of(v), v));
    return t_edges;
  }

  std::vector<vertex_t> graph_config_tconj::leaf_vertices() {
    unsigned int degree[n()];
    for(vertex_t v = 0; v < n(); v++)
      degree[v] = 0;
    std::vector<edge_t> t_edges = tree_edges();
    for(std::size_t ei = 0; ei < t_edges.size(); ei++) {
      degree[t_edges[ei].first]++;
      degree[t_edges[ei].second]++;
    }

    std::vector<vertex_t> l_verts;
    for(vertex_t v = 0; v < n(); v++)
      if(degree[v] < d())
        l_verts.push_back(v);
    return l_verts;
  }

  std::vector<edge_t> graph_config_tconj::leaf_edges() {
    std::vector<vertex_t> l_verts = leaf_vertices();
    std::vector<edge_t> l_edges;
    for(std::size_t i = 0; i < l_verts.size(); i++)
      for(std::size_t j = 0; j < l_verts.size(); j++)
        if(i < j && parent_of(l_verts[j]) != l_verts[i])
          l_edges.push_back(edge_t(l_verts[i], l_verts[j]));
    return l_edges;
  }

}
