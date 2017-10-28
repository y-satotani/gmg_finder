
#ifndef _GMGF_DFS_STATE_MANAGER_HPP_
#define _GMGF_DFS_STATE_MANAGER_HPP_

#include "graph_config.hpp"
#include "initial_builder.hpp"

namespace gmgf {

  template <typename S> class state_manager {
    /*
  protected:
    graph_config* m_config;
    initial_builder* m_builder;
    std::vector<edge_t> m_e_candidate;
    std::vector<std::pair<std::size_t, std::size_t> > m_v_frontier;
    */

  public:
    state_manager() {}
    virtual ~state_manager() {}

    /*
    virtual bool accept_state_change_degree
    (std::size_t ei, S s, bool add) = 0;
    virtual bool accept_state_change_cycle
    (std::size_t ei, S s, bool add) = 0;
    virtual bool accept_state_change_diameter
    (std::size_t ei, S s, bool add) = 0;
    */

    virtual bool can_update_degree
    (graph_config* config,
     S s, edge_t e, bool add,
     std::vector<vertex_t> enter,
     std::vector<vertex_t> exit
     ) = 0;
    virtual bool can_update_cycle
    (graph_config* config,
     S s, edge_t e, bool add,
     std::vector<vertex_t> enter,
     std::vector<vertex_t> exit
     ) = 0;
    virtual bool can_update_diameter
    (graph_config* config,
     S s, edge_t e, bool add,
     std::vector<vertex_t> enter,
     std::vector<vertex_t> exit
     ) = 0;

    bool can_update
    (graph_config* config,
     S s, edge_t e, bool add,
     std::vector<vertex_t> enter,
     std::vector<vertex_t> exit
     ) {
      return can_update_degree(config, s, e, add, enter, exit) &&
        can_update_cycle(config, s, e, add, enter, exit) &&
        can_update_diameter(config, s, e, add, enter, exit);
    }

    virtual bool can_accept_degree(graph_config* config, S s) = 0;
    virtual bool can_accept_cycle(graph_config* config, S s) = 0;
    virtual bool can_accept_diameter(graph_config* config, S s) = 0;

    bool can_accept(graph_config* config, S s) {
      return can_accept_degree(config, s) &&
        can_accept_cycle(config, s) &&
        can_accept_diameter(config, s);
    }

    virtual S initial(graph_config* config, initial_builder* builder) = 0;
    virtual S next(S s, edge_t e, bool add) = 0;
    virtual S failure() = 0;
    virtual void destroy(S s) = 0;
    virtual igraph_t graph(S s) = 0;
  };
}

#endif // _GMGF_DFS_STATE_MANAGER_HPP_
