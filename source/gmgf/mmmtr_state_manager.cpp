
#include "mmmtr_state_manager.hpp"
#include "distance_update.hpp"

namespace gmgf {

  bool mmmtr_state_manager::
  can_update_degree(graph_config* config,
                    igraph_mmmtr_t t, edge_t e, bool add,
                    std::vector<vertex_t> enter,
                    std::vector<vertex_t> exit) {
    return m_bsmgr->can_update_degree(config, t.G, e, add, enter, exit);
  }

  bool mmmtr_state_manager::
  can_update_cycle(graph_config* config,
                   igraph_mmmtr_t t, edge_t e, bool add,
                   std::vector<vertex_t> enter,
                   std::vector<vertex_t> exit) {
    if(!add) return true;
    return igraph_matrix_e(&t.d_min, e.first, e.second) >=
      2*config->Q();
  }

  bool mmmtr_state_manager::
  can_update_diameter(graph_config* config,
                      igraph_mmmtr_t t, edge_t e, bool add,
                      std::vector<vertex_t> enter,
                      std::vector<vertex_t> exit) {
    igraph_integer_t diam = 0;
    if(add) diam = (igraph_integer_t)
              igraph_matrix_max(&t.d_max);
    else {
      igraph_matrix_t d_new, s_new;
      igraph_matrix_init(&d_new, config->n(), config->n());
      igraph_matrix_init(&s_new, config->n(), config->n());
      update_distance_on_delete
        (&d_new, &s_new, &t.d_max, &t.s_max, e.first, e.second);
      diam = (igraph_integer_t) igraph_matrix_max(&d_new);
      igraph_matrix_destroy(&d_new);
      igraph_matrix_destroy(&s_new);
    }
    if(config->R() == 0)
      return (unsigned int) diam <= config->Q();
    else
      return (unsigned int) diam <= config->Q() + 1;
  }

  bool mmmtr_state_manager::
  can_accept_degree(graph_config* config, igraph_mmmtr_t t) {
    return m_bsmgr->can_accept_degree(config, t.G);
  }

  bool mmmtr_state_manager::
  can_accept_cycle(graph_config* config, igraph_mmmtr_t t) {
    return m_bsmgr->can_accept_cycle(config, t.G);
  }

  bool mmmtr_state_manager
  ::can_accept_diameter(graph_config* config, igraph_mmmtr_t t) {
    igraph_integer_t diam = (igraph_integer_t)
      igraph_matrix_max(&t.d_max);
    if(config->R() == 0)
      return (unsigned int) diam <= config->Q();
    else
      return (unsigned int) diam <= config->Q() + 1;
  }

  igraph_mmmtr_t mmmtr_state_manager::
  initial(graph_config* config, initial_builder* builder) {
    igraph_mmmtr_t ret;
    igraph_pair_t p = m_mmmgr->initial(config, builder);
    ret.G = p.first;
    igraph_matrix_init(&ret.d_min, config->n(), config->n());
    igraph_matrix_init(&ret.s_min, config->n(), config->n());
    igraph_matrix_init(&ret.d_max, config->n(), config->n());
    igraph_matrix_init(&ret.s_max, config->n(), config->n());
    set_distance_matrix_with_path_num(&ret.d_min, &ret.s_min, &p.first);
    set_distance_matrix_with_path_num(&ret.d_max, &ret.s_max, &p.second);
    igraph_destroy(&p.second);
    return ret;
  }

  igraph_mmmtr_t mmmtr_state_manager::
  next(igraph_mmmtr_t t, edge_t e, bool add) {
    igraph_mmmtr_t n;
    n.G = m_bsmgr->next(t.G, e, add);

    igraph_integer_t N = igraph_vcount(&t.G);
    igraph_matrix_init(&n.d_min, N, N);
    igraph_matrix_init(&n.s_min, N, N);
    igraph_matrix_init(&n.d_max, N, N);
    igraph_matrix_init(&n.s_max, N, N);

    igraph_integer_t u = e.first;
    igraph_integer_t v = e.second;
    if(add) {
      update_distance_on_insert
        (&n.d_min, &n.s_min, &t.d_min, &t.s_min, u, v);
      igraph_matrix_update(&n.d_max, &t.d_max);
      igraph_matrix_update(&n.s_max, &t.s_max);
    } else {
      igraph_matrix_update(&n.d_min, &t.d_min);
      igraph_matrix_update(&n.s_min, &t.s_min);
      update_distance_on_delete
        (&n.d_max, &n.s_max, &t.d_max, &t.s_max, u, v);
    }
    return n;
  }

  igraph_mmmtr_t mmmtr_state_manager::failure() {
    igraph_mmmtr_t ret;
    igraph_empty(&ret.G, 0, IGRAPH_UNDIRECTED);
    igraph_matrix_init(&ret.d_min, 0, 0);
    igraph_matrix_init(&ret.s_min, 0, 0);
    igraph_matrix_init(&ret.d_max, 0, 0);
    igraph_matrix_init(&ret.s_max, 0, 0);
    return ret;
  }

  void mmmtr_state_manager::destroy(igraph_mmmtr_t t) {
    igraph_destroy(&t.G);
    igraph_matrix_destroy(&t.d_min);
    igraph_matrix_destroy(&t.s_min);
    igraph_matrix_destroy(&t.d_max);
    igraph_matrix_destroy(&t.s_max);
  }

  igraph_t mmmtr_state_manager::graph(igraph_mmmtr_t t) {
    return t.G;
  }

}
