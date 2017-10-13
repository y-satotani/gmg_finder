
#ifndef _CCHECK_MINMAX_STATE_MANAGER_HPP_
#define _CCHECK_MINMAX_STATE_MANAGER_HPP_

extern "C" {
#include <igraph.h>
}
#include <utility>
#include "common/graph_config.hpp"
#include "common/state_manager.hpp"
#include "basic_state_manager.hpp"

namespace ccheck {

  typedef std::pair<igraph_t, igraph_t> igraph_pair_t;

  class minmax_state_manager : public state_manager<igraph_pair_t> {
  protected:
    basic_state_manager* m_bsmgr;
  public:
    minmax_state_manager() { m_bsmgr = new basic_state_manager(); }
    virtual ~minmax_state_manager() { delete m_bsmgr; }

    virtual bool can_update_degree
    (graph_config* config,
     igraph_pair_t t, edge_t e, bool add,
     std::vector<vertex_t> enter,
     std::vector<vertex_t> exit);
    virtual bool can_update_cycle
    (graph_config* config,
     igraph_pair_t t, edge_t e, bool add,
     std::vector<vertex_t> enter,
     std::vector<vertex_t> exit);
    virtual bool can_update_diameter
    (graph_config* config,
     igraph_pair_t t, edge_t e, bool add,
     std::vector<vertex_t> enter,
     std::vector<vertex_t> exit);

    virtual bool can_accept_degree(graph_config* config, igraph_pair_t t);
    virtual bool can_accept_cycle(graph_config* config, igraph_pair_t t);
    virtual bool can_accept_diameter(graph_config* config, igraph_pair_t t);

    virtual igraph_pair_t initial(graph_config* c, initial_builder* b);
    virtual igraph_pair_t next(igraph_pair_t G, edge_t e, bool add);
    virtual igraph_pair_t failure();
    virtual void destroy(igraph_pair_t G);
  };

}

#endif // _CCHECK_MINMAX_STATE_MANAGER_HPP_
