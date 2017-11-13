
#ifndef _GMGF_MMMTR_STATE_MANAGER_HPP_
#define _GMGF_MMMTR_STATE_MANAGER_HPP_

extern "C" {
#include <igraph.h>
}
#include <utility>
#include "basic_state.hpp"

namespace gmgf {

  class mmmtr_state : public basic_state {
  protected:
    igraph_matrix_t d_min, s_min, d_max, s_max;
  public:
    mmmtr_state(graph_config* config, igraph_t G,
                igraph_matrix_t d_min, igraph_matrix_t s_min,
                igraph_matrix_t d_max, igraph_matrix_t s_max);
    mmmtr_state(const mmmtr_state& s);
    virtual ~mmmtr_state();

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

#endif // _GMGF_MMMTR_STATE_MANAGER_HPP_
