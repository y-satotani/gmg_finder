
#include "common/basic_state_manager.hpp"

using namespace gmgf;

namespace gmgf {

  bool basic_state_manager::
  can_update_degree(graph_config* config,
                    igraph_t G, edge_t e, bool add,
                    std::vector<vertex_t> enter,
                    std::vector<vertex_t> exit) {
    igraph_vector_t degree;
    igraph_vector_init(&degree, 0);
    igraph_degree(&G, &degree, igraph_vss_all(),
                  IGRAPH_ALL, 1);

    bool satisfy = true;
    if(add) {
      igraph_integer_t u = e.first;
      igraph_integer_t v = e.second;
      // degree must not exceed d
      satisfy &= igraph_vector_e(&degree, u) < config->d() &&
        igraph_vector_e(&degree, v) < config->d();
    }
    // all of vertices exit from frontier, must have degree d
    // (except selected edge, must have d-1)
    for(std::size_t i = 0; i < exit.size(); i++) {
      igraph_integer_t v = (igraph_integer_t)exit[i];
      if(add) {
        satisfy &= igraph_vector_e(&degree, v) == config->d() - 1;
      } else {
        satisfy &= igraph_vector_e(&degree, v) == config->d();
      }
    }
    igraph_vector_destroy(&degree);

    return satisfy;
  }

  bool basic_state_manager::
  can_update_cycle(graph_config* config,
                   igraph_t G, edge_t e, bool add,
                   std::vector<vertex_t> enter,
                   std::vector<vertex_t> exit) {
    if(!add) return true;

    vertex_t u = e.first;
    vertex_t v = e.second;
    igraph_matrix_t path_length;
    igraph_matrix_init(&path_length, 1, 1);
    igraph_shortest_paths(&G, &path_length,
                          igraph_vss_1(u), igraph_vss_1(v), IGRAPH_ALL);

    bool satisfy = igraph_matrix_e(&path_length, 0, 0) >= 2*config->Q();
    igraph_matrix_destroy(&path_length);
    return satisfy;
  }

  bool basic_state_manager::
  can_update_diameter(graph_config* config,
                      igraph_t G, edge_t e, bool add,
                      std::vector<vertex_t> enter,
                      std::vector<vertex_t> exit) {
    return true;
  }

  bool basic_state_manager::
  can_accept_degree(graph_config* config, igraph_t G) {
    igraph_vector_t degree;
    igraph_vector_init(&degree, 0);
    igraph_degree(&G, &degree, igraph_vss_all(),
                  IGRAPH_ALL, 1);
    bool is_regular = true;
    for(long int i = 0; i < igraph_vector_size(&degree); i++)
      if(igraph_vector_e(&degree, i) != config->d())
        is_regular = false;
    igraph_vector_destroy(&degree);
    return is_regular;
  }

  bool basic_state_manager::
  can_accept_cycle(graph_config* config, igraph_t G) {
    igraph_integer_t girth;
    igraph_girth(&G, &girth, NULL);
    return (unsigned int)girth > 2*config->Q();
  }

  bool basic_state_manager
  ::can_accept_diameter(graph_config* config, igraph_t G) {
    igraph_integer_t diam;
    igraph_diameter(&G, &diam, 0, 0, 0, 0, 0);
    if(config->R() > 0)
      return (unsigned int)diam == config->Q() + 1;
    else
      return (unsigned int)diam == config->Q();
  }

  igraph_t basic_state_manager::
  initial(graph_config* config, initial_builder* builder) {
    igraph_t G;
    igraph_empty(&G, config->n(), IGRAPH_UNDIRECTED);
    std::vector<edge_t> E = builder->initial_edges(config);
    for(std::size_t ei = 0; ei < E.size(); ei++)
      igraph_add_edge(&G, E[ei].first, E[ei].second);
    return G;
  }

  igraph_t basic_state_manager::next(igraph_t G, edge_t e, bool add) {
    igraph_t H;
    igraph_copy(&H, &G);
    if(add)
      igraph_add_edge(&H, e.first, e.second);

    return H;
  }

  igraph_t basic_state_manager::failure() {
    igraph_t G;
    igraph_empty(&G, 0, IGRAPH_UNDIRECTED);
    return G;
  }

  void basic_state_manager::destroy(igraph_t G) {
    igraph_destroy(&G);
  }

}
