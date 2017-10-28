
#include "common/minmax_state_manager.hpp"

using namespace gmgf;

namespace gmgf {

  bool minmax_state_manager::
  can_update_degree(graph_config* config,
                    igraph_pair_t t, edge_t e, bool add,
                    std::vector<vertex_t> enter,
                    std::vector<vertex_t> exit) {
    return m_bsmgr->can_update_degree
      (config, t.first, e, add, enter, exit);
  }

  bool minmax_state_manager::
  can_update_cycle(graph_config* config,
                   igraph_pair_t t, edge_t e, bool add,
                   std::vector<vertex_t> enter,
                   std::vector<vertex_t> exit) {
    return m_bsmgr->can_update_cycle
      (config, t.first, e, add, enter, exit);
  }

  bool minmax_state_manager::
  can_update_diameter(graph_config* config,
                      igraph_pair_t t, edge_t e, bool add,
                      std::vector<vertex_t> enter,
                      std::vector<vertex_t> exit) {
    igraph_integer_t diam;
    if(add) {
      igraph_diameter(&t.second, &diam, 0, 0, 0,
                      IGRAPH_UNDIRECTED, false);
    } else {
      igraph_t H;
      igraph_copy(&H, &t.second);

      igraph_es_t es;
      igraph_es_pairs_small(&es, IGRAPH_UNDIRECTED,
                            e.first, e.second, -1);
      igraph_delete_edges(&H, es);
      igraph_es_destroy(&es);

      igraph_diameter(&H, &diam, 0, 0, 0,
                      IGRAPH_UNDIRECTED, false);

      igraph_destroy(&H);
    }

    if(config->R() == 0)
      return (unsigned int) diam <= config->Q();
    else
      return (unsigned int) diam <= config->Q() + 1;
  }

  bool minmax_state_manager::
  can_accept_degree(graph_config* config, igraph_pair_t t) {
    return m_bsmgr->can_accept_degree(config, t.first);
  }

  bool minmax_state_manager::
  can_accept_cycle(graph_config* config, igraph_pair_t t) {
    return m_bsmgr->can_accept_cycle(config, t.first);
  }

  bool minmax_state_manager
  ::can_accept_diameter(graph_config* config, igraph_pair_t t) {
    return m_bsmgr->can_accept_diameter(config, t.first);
  }

  igraph_pair_t minmax_state_manager::
  initial(graph_config* config, initial_builder* builder) {
    igraph_t G = m_bsmgr->initial(config, builder);
    igraph_t H = m_bsmgr->initial(config, builder);
    // make max graph
    std::vector<edge_t> E = builder->possible_edges(config);
    for(std::size_t ei = 0; ei < E.size(); ei++)
      igraph_add_edge(&H, E[ei].first, E[ei].second);
    return igraph_pair_t(G, H);
  }

  igraph_pair_t minmax_state_manager::
  next(igraph_pair_t t, edge_t e, bool add) {
    igraph_t G = m_bsmgr->next(t.first, e, add);

    igraph_t H;
    igraph_copy(&H, &t.second);
    if(!add) {
      igraph_es_t es;
      igraph_es_pairs_small(&es, IGRAPH_UNDIRECTED,
                            e.first, e.second, -1);
      igraph_delete_edges(&H, es);
      igraph_es_destroy(&es);
    }

    return igraph_pair_t(G, H);
  }

  igraph_pair_t minmax_state_manager::failure() {
    igraph_t G, H;
    igraph_empty(&G, 0, IGRAPH_UNDIRECTED);
    igraph_empty(&H, 0, IGRAPH_UNDIRECTED);
    return igraph_pair_t(G, H);
  }

  void minmax_state_manager::destroy(igraph_pair_t t) {
    igraph_destroy(&t.first);
    igraph_destroy(&t.second);
  }

  igraph_t minmax_state_manager::graph(igraph_pair_t t) {
    return t.first;
  }

}
