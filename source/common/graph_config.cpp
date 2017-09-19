
#include "graph_config.hpp"

namespace ccheck {

  graph_config::graph_config(unsigned int n, unsigned int d) {
    _n = n;
    _d = d;
  }

  unsigned int graph_config::n() {
    return _n;
  }

  unsigned int graph_config::d() {
    return _d;
  }

  unsigned int graph_config::Q() {
    return 0; // TODO
  }

  unsigned int graph_config::R() {
    return 0; // TODO
  }

}
