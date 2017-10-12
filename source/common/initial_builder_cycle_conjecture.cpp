
#include "initial_builder_cycle_conjecture.hpp"
#include <algorithm>

namespace ccheck {

  vertex_t initial_builder_cycle_conjecture::p(graph_config* c) {
    return n_vert_btree(c->Q()-1, c->d());
  }

  vertex_t initial_builder_cycle_conjecture::q(graph_config* c) {
    return p(c) + (n_vert_btree(c->Q(), c->d()) -
                   n_vert_btree(c->Q()-1, c->d())) / c->d();
  }

  vertex_t initial_builder_cycle_conjecture::r(graph_config* c) {
    return c->n() - 2;
  }

  std::vector<edge_t>
  initial_builder_cycle_conjecture::initial_edges(graph_config* c) {
    std::vector<edge_t> t_edges = initial_builder::initial_edges(c);
    if(c->R() > 0) {
      t_edges.push_back(edge_t(p(c), r(c)));
      t_edges.push_back(edge_t(q(c), r(c)));
    }
    return t_edges;
  }

  std::vector<edge_t>
  initial_builder_cycle_conjecture::possible_edges(graph_config* c) {
    std::vector<edge_t> l_edges = initial_builder::possible_edges(c);
    if(c->R() > 0) {
      l_edges.erase(std::remove(l_edges.begin(), l_edges.end(),
                                edge_t(p(c), r(c))));
      l_edges.erase(std::remove(l_edges.begin(), l_edges.end(),
                                edge_t(q(c), r(c))));
    }
    return l_edges;
  }

}
