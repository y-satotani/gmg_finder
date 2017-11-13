
#ifndef _GMGF_INIT_BUILDER_SORTER_HPP_
#define _GMGF_INIT_BUILDER_SORTER_HPP_

extern "C" {
#include <igraph.h>
}
#include <utility>
#include <vector>
#include "graph_initr.hpp"

namespace gmgf {

  class sorted_graph_initr : public graph_initr {
  private:
    graph_initr* m_builder;
  public:
    virtual vertex_t parent_of(vertex_t v);
    virtual std::vector<vertex_t> initial_vertices();
    virtual std::vector<vertex_t> possible_vertices();

  public:
    sorted_graph_initr(graph_initr* builder);
    virtual ~sorted_graph_initr() {}
    virtual std::vector<edge_t> initial_edges();
    virtual std::vector<edge_t> possible_edges();
    //std::vector<std::pair<std::size_t, std::size_t> > vertex_frontier();
    //igraph_t build();
  };

} // end of gmgf

#endif // _GMGF_INIT_BUILDER_SORTER_HPP_
