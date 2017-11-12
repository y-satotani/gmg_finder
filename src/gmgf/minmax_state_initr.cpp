
#include "minmax_state_initr.hpp"

namespace gmgf {

  state* minmax_state_initr::initial(graph_initr* ginitr) {
    igraph_t G = ginitr->build();
    igraph_t H = ginitr->build();
    // make max graph
    std::vector<edge_t> E = ginitr->possible_edges();
    for(std::size_t ei = 0; ei < E.size(); ei++)
      igraph_add_edge(&H, E[ei].first, E[ei].second);
    return new minmax_state(ginitr->get_config(), G, H);
  }

}
