
#ifndef _GMGF_BASIC_STATE_HPP_
#define _GMGF_BASIC_STATE_HPP_

extern "C" {
#include <igraph.h>
}
#include "graph_config.hpp"
#include "state.hpp"

namespace gmgf {

  class basic_state : public state {
  protected:
    igraph_t G;
  public:
    basic_state(graph_config* config, igraph_t G);
    basic_state(const basic_state& s);
    virtual ~basic_state();

    virtual bool can_add_edge_degree
    (edge_t e,
     std::vector<vertex_t> enter,
     std::vector<vertex_t> exit);
    virtual bool can_noadd_edge_degree
    (edge_t e,
     std::vector<vertex_t> enter,
     std::vector<vertex_t> exit);

    virtual bool can_add_edge_cycle
    (edge_t e,
     std::vector<vertex_t> enter,
     std::vector<vertex_t> exit);
    virtual bool can_noadd_edge_cycle
    (edge_t e,
     std::vector<vertex_t> enter,
     std::vector<vertex_t> exit);

    virtual bool can_add_edge_diameter
    (edge_t e,
     std::vector<vertex_t> enter,
     std::vector<vertex_t> exit);
    virtual bool can_noadd_edge_diameter
    (edge_t e,
     std::vector<vertex_t> enter,
     std::vector<vertex_t> exit);

    virtual bool is_final_degree();
    virtual bool is_final_cycle();
    virtual bool is_final_diameter();

    virtual void add_edge(edge_t e);
    virtual void noadd_edge(edge_t e);
    virtual state* copy();

    virtual igraph_t make_graph();
  };

}

#endif // _GMGF_BASIC_STATE_HPP_
