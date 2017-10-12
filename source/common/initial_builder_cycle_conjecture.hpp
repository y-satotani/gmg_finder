
#ifndef _CCHECK_INITIAL_BUILDER_CYCLE_CONJECTURE_
#define _CCHECK_INITIAL_BUILDER_CYCLE_CONJECTURE_

#include <vector>
#include "graph_config.hpp"
#include "initial_builder.hpp"

namespace ccheck {

  class initial_builder_cycle_conjecture : public initial_builder {
  private:
    vertex_t p(graph_config* c);
    vertex_t q(graph_config* c);
    vertex_t r(graph_config* c);
  public:
    virtual ~initial_builder_cycle_conjecture() {}
    std::vector<edge_t> initial_edges(graph_config* c);
    std::vector<edge_t> possible_edges(graph_config* c);
  };
}

#endif // _CCHECK_INITIAL_BUILDER_CYCLE_CONJECTURE_
