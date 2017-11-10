
#include "state.hpp"

namespace gmgf {

  state::state(graph_config* config) {
    m_config = config;
  }

  bool state::can_add_edge(edge_t e,
                           std::vector<vertex_t> enter,
                           std::vector<vertex_t> exit) {
    return can_add_edge_degree(e, enter, exit) &&
      can_add_edge_cycle(e, enter, exit) &&
      can_add_edge_diameter(e, enter, exit);
  }

  bool state::can_noadd_edge(edge_t e,
                             std::vector<vertex_t> enter,
                             std::vector<vertex_t> exit) {
    return can_noadd_edge_degree(e, enter, exit) &&
      can_noadd_edge_cycle(e, enter, exit) &&
      can_noadd_edge_diameter(e, enter, exit);
  }

  bool state::is_final() {
    return is_final_degree() &&
      is_final_cycle() &&
      is_final_diameter();
  }

}
