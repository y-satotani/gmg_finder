
#include "matrix_opt_state.hpp"
#include "distance_update_gmgopt.hpp"

namespace gmgf {

  matrix_opt_state::matrix_opt_state(graph_config* config, igraph_t G,
                                     igraph_matrix_t d_min,
                                     igraph_matrix_t d_max, igraph_matrix_t s_max,
                                     igraph_real_t diam)
    : basic_state(config, G) {
    this->d_min = d_min;
    this->d_max = d_max;
    this->s_max = s_max;
    this->diam = diam;
  }

  matrix_opt_state::matrix_opt_state(const matrix_opt_state& s)
    : basic_state((const basic_state&)s) {
    igraph_matrix_copy(&d_min, &s.d_min);
    igraph_matrix_copy(&d_max, &s.d_max);
    igraph_matrix_copy(&s_max, &s.s_max);
    diam = s.diam;
  }

  matrix_opt_state::~matrix_opt_state() {
    igraph_matrix_destroy(&d_min);
    igraph_matrix_destroy(&d_max);
    igraph_matrix_destroy(&s_max);
  }

  bool matrix_opt_state::can_add_edge_cycle
  (edge_t e, std::vector<vertex_t> enter, std::vector<vertex_t> exit) {
    return igraph_matrix_e(&d_min, e.first, e.second) >= 2*m_config->Q();
  }

  bool matrix_opt_state::can_add_edge_diameter
  (edge_t e, std::vector<vertex_t> enter, std::vector<vertex_t> exit) {
    if(m_config->R() == 0)
      return (unsigned int) diam <= m_config->Q();
    else
      return (unsigned int) diam <= m_config->Q() + 1;
  }

  bool matrix_opt_state::can_noadd_edge_diameter
  (edge_t e, std::vector<vertex_t> enter, std::vector<vertex_t> exit) {
    igraph_real_t diam_new;
    igraph_matrix_t d_new, s_new;
    igraph_matrix_init(&d_new, m_config->n(), m_config->n());
    igraph_matrix_init(&s_new, m_config->n(), m_config->n());
    update_distance_on_delete_gmgopt
      (&d_new, &s_new, &d_max, &s_max, e.first, e.second, &diam_new);
    igraph_matrix_destroy(&d_new);
    igraph_matrix_destroy(&s_new);

    if(m_config->R() == 0)
      return (unsigned int) diam_new <= m_config->Q();
    else
      return (unsigned int) diam_new <= m_config->Q() + 1;
  }

  bool matrix_opt_state::is_final_diameter() {
    if(m_config->R() == 0)
      return (unsigned int) diam <= m_config->Q();
    else
      return (unsigned int) diam <= m_config->Q() + 1;
  }

  void matrix_opt_state::add_edge(edge_t e) {
    basic_state::add_edge(e);
    igraph_matrix_t d;
    igraph_matrix_copy(&d, &d_min);
    update_distance_on_insert_gmgopt
      (&d_min, &d, e.first, e.second);
    igraph_matrix_destroy(&d);
  }

  void matrix_opt_state::noadd_edge(edge_t e) {
    basic_state::noadd_edge(e);
    igraph_matrix_t d, s;
    igraph_matrix_copy(&d, &d_max);
    igraph_matrix_copy(&s, &s_max);
    update_distance_on_delete_gmgopt
      (&d_max, &s_max, &d, &s, e.first, e.second, &diam);
    igraph_matrix_destroy(&d);
    igraph_matrix_destroy(&s);
  }

  state* matrix_opt_state::copy() {
    return new matrix_opt_state(*this);
  }

}
