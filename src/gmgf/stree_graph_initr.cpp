
#include "stree_graph_initr.hpp"

namespace gmgf {

  stree_graph_initr::stree_graph_initr(graph_config* config)
    : graph_initr(config) {
  }

  vertex_t stree_graph_initr::parent_of(vertex_t v) {
    if(v == 0)
      return -1;
    else if(v <= m_config->d())
      return 0;
    else {
      std::size_t depth = tree_depth(v, m_config->d());
      std::size_t n_vert_layer =
        n_vert_btree(depth-1, m_config->d()) - n_vert_btree(depth-2, m_config->d());
      return (v-n_vert_btree(depth-1, m_config->d())) % (n_vert_layer) +
        n_vert_btree(depth-2, m_config->d());
    }
  }

  std::vector<vertex_t> stree_graph_initr::initial_vertices() {
    std::vector<vertex_t> t_verts;
    for(vertex_t v = 0; v < m_config->n(); v++)
      t_verts.push_back(v);
    return t_verts;
  }

  std::vector<vertex_t> stree_graph_initr::possible_vertices() {
    unsigned int degree[m_config->n()];
    for(vertex_t v = 0; v < m_config->n(); v++)
      degree[v] = 0;
    std::vector<edge_t> t_edges = initial_edges();
    for(std::size_t ei = 0; ei < t_edges.size(); ei++) {
      degree[t_edges[ei].first]++;
      degree[t_edges[ei].second]++;
    }

    std::vector<vertex_t> l_verts;
    for(vertex_t v = 0; v < m_config->n(); v++)
      if(degree[v] < m_config->d())
        l_verts.push_back(v);
    return l_verts;
  }

  std::vector<edge_t> stree_graph_initr::initial_edges() {
    std::vector<edge_t> t_edges;
    for(vertex_t v = 1; v < m_config->n(); v++)
      t_edges.push_back(edge_t(parent_of(v), v));
    return t_edges;
  }

  std::vector<edge_t> stree_graph_initr::possible_edges() {
    std::vector<vertex_t> l_verts = possible_vertices();
    std::vector<edge_t> l_edges;
    for(std::size_t i = 0; i < l_verts.size(); i++)
      for(std::size_t j = 0; j < l_verts.size(); j++)
        if(i < j && parent_of(l_verts[j]) != l_verts[i])
          l_edges.push_back(edge_t(l_verts[i], l_verts[j]));
    return l_edges;
  }

}
