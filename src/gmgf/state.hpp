
#ifndef _GMGF_STATE_HPP_
#define _GMGF_STATE_HPP_

#include "graph_config.hpp"

namespace gmgf {

  class state {
  protected:
    graph_config* m_config;
  public:
    state(graph_config* config);
    virtual ~state() {};

    bool can_add_edge
    (edge_t e,
     std::vector<vertex_t> enter,
     std::vector<vertex_t> exit);

    bool can_noadd_edge
    (edge_t e,
     std::vector<vertex_t> enter,
     std::vector<vertex_t> exit);

    bool is_final();

    virtual bool can_add_edge_degree
    (edge_t e,
     std::vector<vertex_t> enter,
     std::vector<vertex_t> exit) = 0;
    virtual bool can_noadd_edge_degree
    (edge_t e,
     std::vector<vertex_t> enter,
     std::vector<vertex_t> exit) = 0;

    virtual bool can_add_edge_cycle
    (edge_t e,
     std::vector<vertex_t> enter,
     std::vector<vertex_t> exit) = 0;
    virtual bool can_noadd_edge_cycle
    (edge_t e,
     std::vector<vertex_t> enter,
     std::vector<vertex_t> exit) = 0;

    virtual bool can_add_edge_diameter
    (edge_t e,
     std::vector<vertex_t> enter,
     std::vector<vertex_t> exit) = 0;
    virtual bool can_noadd_edge_diameter
    (edge_t e,
     std::vector<vertex_t> enter,
     std::vector<vertex_t> exit) = 0;

    virtual bool is_final_degree() = 0;
    virtual bool is_final_cycle() = 0;
    virtual bool is_final_diameter() = 0;

    virtual void add_edge(edge_t e) = 0;
    virtual void noadd_edge(edge_t e) = 0;
    virtual state* copy() = 0;

    virtual igraph_t make_graph() = 0;
  };

}

#endif // _GMGF_STATE_HPP_
