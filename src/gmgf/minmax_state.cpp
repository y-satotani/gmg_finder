
#include "minmax_state.hpp"

namespace gmgf {

  minmax_state::minmax_state(graph_config* config, igraph_t G, igraph_t H)
    : basic_state(config, G) {
    this->H = H;
  }

  minmax_state::minmax_state(const minmax_state& s)
    : basic_state((const basic_state&)s) {
    //igraph_copy(&this->G, &s.G);
    igraph_copy(&this->H, &s.H);
  }

  minmax_state::~minmax_state() {
    igraph_destroy(&G);
    igraph_destroy(&H);
  }

  bool minmax_state::can_add_edge_degree
  (edge_t e,
   std::vector<vertex_t> enter,
   std::vector<vertex_t> exit) {
    return basic_state::can_add_edge_degree(e, enter, exit);
  }

  bool minmax_state::can_noadd_edge_degree
  (edge_t e,
   std::vector<vertex_t> enter,
   std::vector<vertex_t> exit) {
    return basic_state::can_noadd_edge_degree(e, enter, exit);
  }

  bool minmax_state::can_add_edge_cycle
  (edge_t e,
   std::vector<vertex_t> enter,
   std::vector<vertex_t> exit) {
    return basic_state::can_add_edge_cycle(e, enter, exit);
  }

  bool minmax_state::can_noadd_edge_cycle
  (edge_t e,
   std::vector<vertex_t> enter,
   std::vector<vertex_t> exit) {
    return basic_state::can_noadd_edge_cycle(e, enter, exit);
  }

  bool minmax_state::can_add_edge_diameter
  (edge_t e,
   std::vector<vertex_t> enter,
   std::vector<vertex_t> exit) {
    igraph_integer_t diam;
    igraph_diameter(&H, &diam, 0, 0, 0,
                    IGRAPH_UNDIRECTED, false);
    if(m_config->R() == 0)
      return (unsigned int) diam <= m_config->Q();
    else
      return (unsigned int) diam <= m_config->Q() + 1;
  }

  bool minmax_state::can_noadd_edge_diameter
  (edge_t e,
   std::vector<vertex_t> enter,
   std::vector<vertex_t> exit) {
    igraph_integer_t diam;

    igraph_t _H;
    igraph_es_t es;
    igraph_copy(&_H, &H);
    igraph_es_pairs_small(&es, IGRAPH_UNDIRECTED,
                          e.first, e.second, -1);
    igraph_delete_edges(&_H, es);
    igraph_es_destroy(&es);
    igraph_diameter(&_H, &diam, 0, 0, 0,
                    IGRAPH_UNDIRECTED, false);
    igraph_destroy(&_H);

    if(m_config->R() == 0)
      return (unsigned int) diam <= m_config->Q();
    else
      return (unsigned int) diam <= m_config->Q() + 1;
  }

  bool minmax_state::is_final_degree() {
    return basic_state::is_final_degree();
  }

  bool minmax_state::is_final_cycle() {
    return basic_state::is_final_cycle();
  }

  bool minmax_state::is_final_diameter() {
    return basic_state::is_final_diameter();
  }

  void minmax_state::add_edge(edge_t e) {
    igraph_add_edge(&G, e.first, e.second);
  }

  void minmax_state::noadd_edge(edge_t e) {
    igraph_es_t es;
    igraph_es_pairs_small(&es, IGRAPH_UNDIRECTED,
                          e.first, e.second, -1);
    igraph_delete_edges(&H, es);
    igraph_es_destroy(&es);
  }

  state* minmax_state::copy() {
    return new minmax_state(*this);
  }

  igraph_t minmax_state::make_graph() {
    return basic_state::make_graph();
  }

}
