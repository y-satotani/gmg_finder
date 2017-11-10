
#include "mmmtr_state_initr.hpp"
#include "distance_update.hpp"

namespace gmgf {

  state* mmmtr_state_initr::initial(graph_initr* ginitr) {
    graph_config* config = ginitr->get_config();
    igraph_t G = ginitr->build();
    igraph_t H = ginitr->build();
    // make max graph
    std::vector<edge_t> E = ginitr->possible_edges();
    for(std::size_t ei = 0; ei < E.size(); ei++)
      igraph_add_edge(&H, E[ei].first, E[ei].second);
    // make matrix
    igraph_matrix_t d_min, s_min, d_max, s_max;
    unsigned int N = config->n();
    igraph_matrix_init(&d_min, N, N);
    igraph_matrix_init(&s_min, N, N);
    igraph_matrix_init(&d_max, N, N);
    igraph_matrix_init(&s_max, N, N);
    set_distance_matrix_with_path_num(&d_min, &s_min, &G);
    set_distance_matrix_with_path_num(&d_max, &s_max, &H);
    igraph_destroy(&H);
    return new mmmtr_state(config, G, d_min, s_min, d_max, s_max);
  }

}
