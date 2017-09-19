
#include "graph_config.hpp"
#include <cmath>

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

  unsigned int graph_config::depth(int vid) {
    if(vid <= 0)
      return 0;
    else
      return (unsigned int)(log((vid-1.)*(_d-2.)/_d+1) / log(_d-1)) + 1;
  }

  unsigned int graph_config::Q() {
    return 0; // TODO
  }

  unsigned int graph_config::R() {
    return 0; // TODO
  }

  igraph_t graph_config::build_base_graph() {
    igraph_t graph;
    igraph_empty(&graph, _n, IGRAPH_UNDIRECTED);
    return graph;
  }

}
