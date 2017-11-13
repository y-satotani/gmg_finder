
#ifndef _GMGF_CYCLE_GRAPH_INITIALIZER_HPP_
#define _GMGF_CYCLE_GRAPH_INTIIALIZER_HPP_

#include <vector>
#include "basic_graph_initr.hpp"

namespace gmgf {

  class cycle_graph_initr : public basic_graph_initr {
  private:
    vertex_t p();
    vertex_t q();
    vertex_t r();
  public:
    cycle_graph_initr(graph_config* config);
    virtual ~cycle_graph_initr() {}
    std::vector<edge_t> initial_edges();
    std::vector<edge_t> possible_edges();
  };
}

#endif // _GMGF_CYCLE_GRAPH_INITIALIZER_HPP_
