
#ifndef _GMGF_BASIC_GRAPH_INITIALIZER_HPP_
#define _GMGF_BASIC_GRAPH_INITIALIZER_HPP_

extern "C" {
#include <igraph.h>
}
#include <utility>
#include <vector>
#include "graph_initr.hpp"

namespace gmgf {

  class basic_graph_initr : public graph_initr {
  public:
    basic_graph_initr(graph_config* config);
    virtual ~basic_graph_initr() {}

  private:
    vertex_t parent_of(vertex_t v);
    std::vector<vertex_t> initial_vertices();
    std::vector<vertex_t> possible_vertices();

  public:
    virtual std::vector<edge_t> initial_edges();
    virtual std::vector<edge_t> possible_edges();
  };

} // end of gmgf

#endif // _GMGF_BASIC_GRAPH_INITIALIZER_HPP_
