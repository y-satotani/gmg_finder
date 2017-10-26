
#ifndef _CCHECK_INIT_BUILDER_SORTER_HPP_
#define _CCHECK_INIT_BUILDER_SORTER_HPP_

extern "C" {
#include <igraph.h>
}
#include <utility>
#include <vector>
#include "graph_config.hpp"
#include "initial_builder.hpp"

namespace ccheck {

  class initial_builder_sorter : public initial_builder {
  private:
    initial_builder* m_builder;
  public:
    virtual vertex_t parent_of(graph_config* c, vertex_t v);
    virtual std::vector<vertex_t> initial_vertices(graph_config* c);
    virtual std::vector<vertex_t> possible_vertices(graph_config* c);

  public:
    initial_builder_sorter(initial_builder* builder);
    virtual ~initial_builder_sorter() {}
    virtual std::vector<edge_t> initial_edges(graph_config* c);
    virtual std::vector<edge_t> possible_edges(graph_config* c);
    std::vector<std::pair<std::size_t, std::size_t> >
    vertex_frontier(graph_config* c);
    igraph_t build(graph_config* c);
  };

} // end of ccheck

#endif // _CCHECK_INIT_BUILDER_SORTER_HPP_
