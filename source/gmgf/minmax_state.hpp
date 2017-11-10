
#ifndef _GMGF_MINMAX_STATE_HPP_
#define _GMGF_MINMAX_STATE_HPP_

extern "C" {
#include <igraph.h>
}
#include <utility>
#include "graph_config.hpp"
#include "basic_state.hpp"

namespace gmgf {

  typedef std::pair<igraph_t, igraph_t> igraph_pair_t;

  class minmax_state : public basic_state {
  protected:
    igraph_t H;
  public:
    minmax_state(graph_config* config, igraph_t G, igraph_t H);
    minmax_state(const minmax_state& s);
    virtual ~minmax_state();

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

#endif // _GMGF_MINMAX_STATE_HPP_
