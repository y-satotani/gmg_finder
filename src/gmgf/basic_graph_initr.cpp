
#include "basic_graph_initr.hpp"

#include <cmath>

namespace gmgf {

  basic_graph_initr::basic_graph_initr(graph_config* config)
    : graph_initr(config) {
  }

  vertex_t basic_graph_initr::parent_of(vertex_t v) {
    if(v == 0)
      return -1;
    else if(v <= m_config->d())
      return 0;
    else {
      unsigned int depth = tree_depth(v, m_config->d());
      return (v-n_vert_btree(depth-1, m_config->d())) / (m_config->d()-1) +
        n_vert_btree(depth-2, m_config->d());
    }
  }

  std::vector<vertex_t> basic_graph_initr::initial_vertices() {
    std::vector<vertex_t> t_verts;
    for(vertex_t v = 0; v < n_vert_btree(m_config->Q(), m_config->d()); v++)
      t_verts.push_back(v);
    return t_verts;
  }

  std::vector<vertex_t> basic_graph_initr::possible_vertices() {
    std::vector<vertex_t> leaves;
    for(vertex_t v = n_vert_btree(m_config->Q() - 1, m_config->d());
        v < m_config->n(); v++)
      leaves.push_back(v);
    return leaves;
  }

  std::vector<edge_t> basic_graph_initr::initial_edges() {
    std::vector<edge_t> t_edges;
    std::vector<vertex_t> t_verts = initial_vertices();
    for(std::size_t i = 0; i < t_verts.size(); i++)
      if(t_verts[i] > 0)
        t_edges.push_back(edge_t(parent_of(t_verts[i]), t_verts[i]));
    return t_edges;
  }

  std::vector<edge_t> basic_graph_initr::possible_edges() {
    std::vector<edge_t> l_edges;
    std::vector<vertex_t> leaves = possible_vertices();
    for(std::size_t i = 0; i < leaves.size(); i++)
      for(std::size_t j = 0; j < leaves.size(); j++)
        if(i < j)
          l_edges.push_back(edge_t(leaves[i], leaves[j]));
    return l_edges;
  }

}
