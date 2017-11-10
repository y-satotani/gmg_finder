
#ifndef _GMGF_BASIC_GRAPH_INITIALIZER_HPP_
#define _GMGF_BASIC_GRAPH_INITIALIZER_HPP_

extern "C" {
#include <igraph.h>
}
#include <utility>
#include <vector>
#include "graph_config.hpp"
#include "graph_initr.hpp"

namespace gmgf {

  class basic_graph_initr : public graph_initr {
  public:
    basic_graph_initr(graph_config* config);
    virtual ~basic_graph_initr() {}

  public:
    virtual vertex_t parent_of(vertex_t v);
    virtual std::vector<vertex_t> initial_vertices();
    virtual std::vector<vertex_t> possible_vertices();

  public:
    virtual std::vector<edge_t> initial_edges();
    virtual std::vector<edge_t> possible_edges();
    std::vector<std::pair<std::size_t, std::size_t> > vertex_frontier();
    igraph_t build();
  };

} // end of gmgf

#endif // _GMGF_BASIC_GRAPH_INITIALIZER_HPP_
