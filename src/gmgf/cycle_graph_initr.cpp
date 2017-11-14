
#include "cycle_graph_initr.hpp"
#include <algorithm>

namespace gmgf {

  cycle_graph_initr::
  cycle_graph_initr(graph_config* config)
    : basic_graph_initr(config) {
  }

  vertex_t cycle_graph_initr::p() {
    return n_vert_btree(m_config->Q()-1, m_config->d());
  }

  vertex_t cycle_graph_initr::q() {
    return p() + (n_vert_btree(m_config->Q(), m_config->d()) -
                   n_vert_btree(m_config->Q()-1, m_config->d())) /
      m_config->d();
  }

  vertex_t cycle_graph_initr::r() {
    return m_config->n() - m_config->R();
  }

  std::vector<edge_t>
  cycle_graph_initr::initial_edges() {
    std::vector<edge_t> t_edges = basic_graph_initr::initial_edges();
    if(m_config->R() > 0) {
      t_edges.push_back(edge_t(p(), r()));
      t_edges.push_back(edge_t(q(), r()));
    }
    return t_edges;
  }

  std::vector<edge_t>
  cycle_graph_initr::possible_edges() {
    std::vector<edge_t> l_edges = basic_graph_initr::possible_edges();
    if(m_config->R() > 0) {
      l_edges.erase(std::remove(l_edges.begin(), l_edges.end(),
                                edge_t(p(), r())));
      l_edges.erase(std::remove(l_edges.begin(), l_edges.end(),
                                edge_t(q(), r())));
    }
    return l_edges;
  }

}
