
#ifndef _GMGF_DFS_FINDER_HPP_
#define _GMGF_DFS_FINDER_HPP_

extern "C" {
#include <igraph.h>
}
#include <utility>
#include <vector>
#include "graph_config.hpp"
#include "graph_initr.hpp"
#include "state_initr.hpp"
#include "state.hpp"

namespace gmgf {

  class dfs_finder {
  protected:
    state_initr* m_sinitr;
    graph_initr* m_ginitr;
    std::vector<std::pair<std::size_t, state*> > m_stack;
    std::vector<edge_t> m_e_possible;
    std::vector<std::pair<std::size_t, std::size_t> > m_v_range;
    unsigned long long m_extracted_nodes;

  public:
    dfs_finder(graph_initr* ginitr, state_initr* sinitr);
    virtual ~dfs_finder();

    unsigned long long extracted_nodes();
    void reset();
    igraph_t next();

  };
}

#endif // _GMGF_DFS_FINDER_HPP_
