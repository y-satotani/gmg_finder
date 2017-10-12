
#ifndef _CCHECK_INITIAL_BUILDER_STREE_CONJECTURE_HPP_
#define _CCHECK_INITIAL_BUILDER_STREE_CONJECTURE_HPP_

#include <vector>
#include "graph_config.hpp"
#include "initial_builder.hpp"

namespace ccheck {

  class initial_builder_stree_conjecture : public initial_builder {
  protected:
    vertex_t parent_of(graph_config* c, vertex_t v);
    std::vector<vertex_t> initial_vertices(graph_config* c);
    std::vector<vertex_t> possible_vertices(graph_config* c);
  public:
    virtual ~initial_builder_stree_conjecture() {}
    std::vector<edge_t> initial_edges(graph_config* c);
    std::vector<edge_t> possible_edges(graph_config* c);
  };
}

#endif // _CCHECK_GRAPH_CONFIG_TCONJ_HPP_
