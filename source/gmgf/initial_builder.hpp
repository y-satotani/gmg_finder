
#ifndef _GMGF_INIT_BUILDER_HPP_
#define _GMGF_INIT_BUILDER_HPP_

extern "C" {
#include <igraph.h>
}
#include <utility>
#include <vector>
#include "graph_config.hpp"

namespace gmgf {

  class initial_builder {
  public:
    virtual vertex_t parent_of(graph_config* c, vertex_t v);
    virtual std::vector<vertex_t> initial_vertices(graph_config* c);
    virtual std::vector<vertex_t> possible_vertices(graph_config* c);

  public:
    virtual ~initial_builder() {}
    virtual std::vector<edge_t> initial_edges(graph_config* c);
    virtual std::vector<edge_t> possible_edges(graph_config* c);
    std::vector<std::pair<std::size_t, std::size_t> >
    vertex_frontier(graph_config* c);
    igraph_t build(graph_config* c);
  };

} // end of gmgf

#endif // _GMGF_INIT_BUILDER_HPP_
