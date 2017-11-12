
#ifndef _GMGF_GRAPH_INITR_HPP_
#define _GMGF_GRAPH_INITR_HPP_

extern "C" {
#include <igraph.h>
}
#include <utility>
#include <vector>
#include "graph_config.hpp"

namespace gmgf {

  class graph_initr {
  protected:
    graph_config* m_config;
  public:
    graph_initr(graph_config* config);
    virtual ~graph_initr() {}
    graph_config* get_config();

    virtual vertex_t parent_of(vertex_t v) = 0;
    virtual std::vector<vertex_t> initial_vertices() = 0;
    virtual std::vector<vertex_t> possible_vertices() = 0;
    virtual std::vector<edge_t> initial_edges() = 0;
    virtual std::vector<edge_t> possible_edges() = 0;
    virtual std::vector<std::pair<std::size_t, std::size_t> > vertex_frontier();
    virtual igraph_t build();
  };

} // end of gmgf

#endif // _GMGF_GRAPH_INITR_HPP_
