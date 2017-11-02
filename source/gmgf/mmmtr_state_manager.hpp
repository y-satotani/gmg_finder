
#ifndef _GMGF_MMMTR_STATE_MANAGER_HPP_
#define _GMGF_MMMTR_STATE_MANAGER_HPP_

extern "C" {
#include <igraph.h>
}
#include <utility>
#include "graph_config.hpp"
#include "state_manager.hpp"
#include "basic_state_manager.hpp"
#include "minmax_state_manager.hpp"

namespace gmgf {

  struct _igraph_with_minmax_matrix {
    igraph_t G;
    igraph_matrix_t d_min;
    igraph_matrix_t s_min;
    igraph_matrix_t d_max;
    igraph_matrix_t s_max;
  };
  typedef _igraph_with_minmax_matrix igraph_mmmtr_t;

  class mmmtr_state_manager : public state_manager<igraph_mmmtr_t> {
  protected:
    basic_state_manager* m_bsmgr;
    minmax_state_manager* m_mmmgr;
  public:
    mmmtr_state_manager() {
      m_bsmgr = new basic_state_manager();
      m_mmmgr = new minmax_state_manager();
    }
    virtual ~mmmtr_state_manager() {
      delete m_bsmgr;
      delete m_mmmgr;
    }

    virtual bool can_update_degree
    (graph_config* config,
     igraph_mmmtr_t t, edge_t e, bool add,
     std::vector<vertex_t> enter,
     std::vector<vertex_t> exit);
    virtual bool can_update_cycle
    (graph_config* config,
     igraph_mmmtr_t t, edge_t e, bool add,
     std::vector<vertex_t> enter,
     std::vector<vertex_t> exit);
    virtual bool can_update_diameter
    (graph_config* config,
     igraph_mmmtr_t t, edge_t e, bool add,
     std::vector<vertex_t> enter,
     std::vector<vertex_t> exit);

    virtual bool can_accept_degree(graph_config* config, igraph_mmmtr_t t);
    virtual bool can_accept_cycle(graph_config* config, igraph_mmmtr_t t);
    virtual bool can_accept_diameter(graph_config* config, igraph_mmmtr_t t);

    virtual igraph_mmmtr_t initial(graph_config* c, initial_builder* b);
    virtual igraph_mmmtr_t next(igraph_mmmtr_t G, edge_t e, bool add);
    virtual igraph_mmmtr_t failure();
    virtual void destroy(igraph_mmmtr_t G);
    virtual igraph_t graph(igraph_mmmtr_t G);
  };

}

#endif // _GMGF_MMMTR_STATE_MANAGER_HPP_
