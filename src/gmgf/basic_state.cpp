
#include "basic_state.hpp"

namespace gmgf {

  basic_state::basic_state(graph_config* config, igraph_t G)
    : state(config) {
    this->G = G;
  }

  basic_state::basic_state(const basic_state& s)
    : state(s.m_config) {
    igraph_copy(&this->G, &s.G);
  }

  basic_state::~basic_state() {
    igraph_destroy(&G);
  }

  bool basic_state::can_add_edge_degree
  (edge_t e,
   std::vector<vertex_t> enter,
   std::vector<vertex_t> exit) {
    igraph_vector_t degree;
    igraph_vector_init(&degree, 0);
    igraph_degree(&G, &degree, igraph_vss_all(),
                  IGRAPH_ALL, 1);

    bool satisfy = true;

    igraph_integer_t u = e.first;
    igraph_integer_t v = e.second;
    // degree must not exceed d
    satisfy &= igraph_vector_e(&degree, u) < m_config->d() &&
      igraph_vector_e(&degree, v) < m_config->d();

    // all of the vertices exit from frontier, must have degree d
    // (except selected edge, must have d-1)
    for(std::size_t i = 0; i < exit.size(); i++) {
      igraph_integer_t w = (igraph_integer_t)exit[i];
      satisfy &= igraph_vector_e(&degree, w) == m_config->d() - 1;
    }
    igraph_vector_destroy(&degree);

    return satisfy;
  }

  bool basic_state::can_noadd_edge_degree
  (edge_t e,
   std::vector<vertex_t> enter,
   std::vector<vertex_t> exit) {
    igraph_vector_t degree;
    igraph_vector_init(&degree, 0);
    igraph_degree(&G, &degree, igraph_vss_all(),
                  IGRAPH_ALL, 1);

    bool satisfy = true;

    // all of the vertices exit from frontier, must have degree d
    // (except selected edge, must have d-1)
    for(std::size_t i = 0; i < exit.size(); i++) {
      igraph_integer_t w = (igraph_integer_t)exit[i];
      satisfy &= igraph_vector_e(&degree, w) == m_config->d();
    }
    igraph_vector_destroy(&degree);

    return satisfy;
  }

  bool basic_state::can_add_edge_cycle
  (edge_t e,
   std::vector<vertex_t> enter,
   std::vector<vertex_t> exit) {
    vertex_t u = e.first;
    vertex_t v = e.second;
    igraph_matrix_t path_length;
    igraph_matrix_init(&path_length, 1, 1);
    igraph_shortest_paths(&G, &path_length,
                          igraph_vss_1(u), igraph_vss_1(v),
                          IGRAPH_ALL);

    bool satisfy =
      igraph_matrix_e(&path_length, 0, 0) >= 2*m_config->Q();
    igraph_matrix_destroy(&path_length);
    return satisfy;
  }

  bool basic_state::can_noadd_edge_cycle
  (edge_t e,
   std::vector<vertex_t> enter,
   std::vector<vertex_t> exit) {
    return true;
  }

  bool basic_state::can_add_edge_diameter
  (edge_t e,
   std::vector<vertex_t> enter,
   std::vector<vertex_t> exit) {
    return true;
  }

  bool basic_state::can_noadd_edge_diameter
  (edge_t e,
   std::vector<vertex_t> enter,
   std::vector<vertex_t> exit) {
    return true;
  }

  bool basic_state::is_final_degree() {
    igraph_vector_t degree;
    igraph_vector_init(&degree, 0);
    igraph_degree(&G, &degree, igraph_vss_all(),
                  IGRAPH_ALL, 1);
    bool is_regular = true;
    for(long int i = 0; i < igraph_vector_size(&degree); i++)
      if(igraph_vector_e(&degree, i) != m_config->d())
        is_regular = false;
    igraph_vector_destroy(&degree);
    return is_regular;
  }

  bool basic_state::is_final_cycle() {
    igraph_integer_t girth;
    igraph_girth(&G, &girth, NULL);
    return (unsigned int)girth > 2*m_config->Q();
  }

  bool basic_state::is_final_diameter() {
    igraph_integer_t diam;
    igraph_diameter(&G, &diam, 0, 0, 0, 0, 0);
    if(m_config->R() > 0)
      return (unsigned int)diam == m_config->Q() + 1;
    else
      return (unsigned int)diam == m_config->Q();
  }

  void basic_state::add_edge(edge_t e) {
    igraph_add_edge(&G, e.first, e.second);
  }

  void basic_state::noadd_edge(edge_t e) {

  }

  state* basic_state::copy() {
    return new basic_state(*this);
  }

  igraph_t basic_state::make_graph() {
    igraph_t H;
    igraph_copy(&H, &G);
    return H;
  }

  bool basic_state::is_isomorphic(state* state) {
    igraph_t H = ((basic_state*) state)->G;
    igraph_bool_t iso;
    igraph_isomorphic(&G, &H, &iso);
    return iso;
  }

}
