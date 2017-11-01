
#ifndef _GMGF_BASIC_STATE_MANAGER_HPP_
#define _GMGF_BASIC_STATE_MANAGER_HPP_

extern "C" {
#include <igraph.h>
}
#include "graph_config.hpp"
#include "state_manager.hpp"

namespace gmgf {

  class basic_state_manager : public state_manager<igraph_t> {
  public:
    basic_state_manager() {}
    virtual ~basic_state_manager() {}

    virtual bool can_update_degree
    (graph_config* config,
     igraph_t G, edge_t e, bool add,
     std::vector<vertex_t> enter,
     std::vector<vertex_t> exit);
    virtual bool can_update_cycle
    (graph_config* config,
     igraph_t G, edge_t e, bool add,
     std::vector<vertex_t> enter,
     std::vector<vertex_t> exit);
    virtual bool can_update_diameter
    (graph_config* config,
     igraph_t G, edge_t e, bool add,
     std::vector<vertex_t> enter,
     std::vector<vertex_t> exit);

    virtual bool can_accept_degree(graph_config* config, igraph_t G);
    virtual bool can_accept_cycle(graph_config* config, igraph_t G);
    virtual bool can_accept_diameter(graph_config* config, igraph_t G);

    virtual igraph_t initial(graph_config* config, initial_builder* builder);
    virtual igraph_t next(igraph_t G, edge_t e, bool add);
    virtual igraph_t failure();
    virtual void destroy(igraph_t G);
    virtual igraph_t graph(igraph_t G);
  };

}

#endif // _GMGF_BASIC_STATE_MANAGER_HPP_
