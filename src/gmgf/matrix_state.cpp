
#include "matrix_state.hpp"
#include "distance_update.hpp"

namespace gmgf {

  matrix_state::matrix_state(graph_config* config, igraph_t G,
                     igraph_matrix_t d_min, igraph_matrix_t s_min,
                     igraph_matrix_t d_max, igraph_matrix_t s_max)
    : basic_state(config, G) {
    this->d_min = d_min;
    this->s_min = s_min;
    this->d_max = d_max;
    this->s_max = s_max;
  }

  matrix_state::matrix_state(const matrix_state& s)
    : basic_state((const basic_state&)s) {
    igraph_matrix_copy(&d_min, &s.d_min);
    igraph_matrix_copy(&s_min, &s.s_min);
    igraph_matrix_copy(&d_max, &s.d_max);
    igraph_matrix_copy(&s_max, &s.s_max);
  }

  matrix_state::~matrix_state() {
    igraph_matrix_destroy(&d_min);
    igraph_matrix_destroy(&s_min);
    igraph_matrix_destroy(&d_max);
    igraph_matrix_destroy(&s_max);
  }

  bool matrix_state::can_add_edge_cycle
  (edge_t e, std::vector<vertex_t> enter, std::vector<vertex_t> exit) {
    return igraph_matrix_e(&d_min, e.first, e.second) >= 2*m_config->Q();
  }

  bool matrix_state::can_add_edge_diameter
  (edge_t e, std::vector<vertex_t> enter, std::vector<vertex_t> exit) {
    unsigned int diam = (unsigned int) igraph_matrix_max(&d_max);
    if(m_config->R() == 0)
      return diam <= m_config->Q();
    else
      return diam <= m_config->Q() + 1;
  }

  bool matrix_state::can_noadd_edge_diameter
  (edge_t e, std::vector<vertex_t> enter, std::vector<vertex_t> exit) {
    unsigned int diam;
    igraph_matrix_t d_new, s_new;
    igraph_matrix_init(&d_new, m_config->n(), m_config->n());
    igraph_matrix_init(&s_new, m_config->n(), m_config->n());
    update_distance_on_delete
      (&d_new, &s_new, &d_max, &s_max, e.first, e.second);
    diam = (unsigned int) igraph_matrix_max(&d_new);
    igraph_matrix_destroy(&d_new);
    igraph_matrix_destroy(&s_new);

    if(m_config->R() == 0)
      return diam <= m_config->Q();
    else
      return diam <= m_config->Q() + 1;
  }

  bool matrix_state::is_final_diameter() {
    unsigned int diam = (unsigned int) igraph_matrix_max(&d_max);
    if(m_config->R() == 0)
      return diam <= m_config->Q();
    else
      return diam <= m_config->Q() + 1;
  }

  void matrix_state::add_edge(edge_t e) {
    basic_state::add_edge(e);
    igraph_matrix_t d, s;
    igraph_matrix_copy(&d, &d_min);
    igraph_matrix_copy(&s, &s_min);
    update_distance_on_insert
      (&d_min, &s_min, &d, &s, e.first, e.second);
    igraph_matrix_destroy(&d);
    igraph_matrix_destroy(&s);
  }

  void matrix_state::noadd_edge(edge_t e) {
    basic_state::noadd_edge(e);
    igraph_matrix_t d, s;
    igraph_matrix_copy(&d, &d_max);
    igraph_matrix_copy(&s, &s_max);
    update_distance_on_delete
      (&d_max, &s_max, &d, &s, e.first, e.second);
    igraph_matrix_destroy(&d);
    igraph_matrix_destroy(&s);
  }

  state* matrix_state::copy() {
    return new matrix_state(*this);
  }

}
