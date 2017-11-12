
#ifndef _GMGF_STREE_GRAPH_INITIALIZER_HPP_
#define _GMGF_STREE_GRAPH_INITIALIZER_HPP_

#include <vector>
#include "graph_config.hpp"
#include "basic_graph_initr.hpp"

namespace gmgf {

  class stree_graph_initr : public basic_graph_initr {
  public:
    vertex_t parent_of(vertex_t v);
    std::vector<vertex_t> initial_vertices();
    std::vector<vertex_t> possible_vertices();
  public:
    stree_graph_initr(graph_config* config);
    virtual ~stree_graph_initr() {}
    std::vector<edge_t> initial_edges();
    std::vector<edge_t> possible_edges();
  };
}

#endif // _GMGF_STREE_GRAPH_INITIALIZER_HPP_
