
#include "basic_state_initr.hpp"

namespace gmgf {

  state* basic_state_initr::initial(graph_initr* ginitr) {
    igraph_t G = ginitr->build();
    return new basic_state(ginitr->get_config(), G);
  }

}
