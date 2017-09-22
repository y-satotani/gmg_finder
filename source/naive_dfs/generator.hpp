
#ifndef _CCHECK_NAIVE_DFS_GENERATOR_HPP_
#define _CCHECK_NAIVE_DFS_GENERATOR_HPP_

extern "C" {
#include <igraph.h>
}
#include <utility>
#include <vector>
#include "common/graph_config.hpp"

namespace ccheck {

  typedef std::pair<std::size_t, igraph_t> dfs_node_t;

  class dfs_generator {
  private:
    ccheck::graph_config* m_config;
    std::vector<dfs_node_t> m_stack;
    std::vector<edge_t> m_edges;
    std::vector<std::pair<int, int> > m_vert_range;
    bool degree_constraint(std::size_t ei, igraph_t* G, bool add);
    bool cycle_constraint(std::size_t ei, igraph_t* G, bool add);
    bool degree_constraint(igraph_t* G);
    bool diameter_constraint(igraph_t* G);
  public:
    dfs_generator(graph_config* conf);
    ~dfs_generator();
    void reset();
    igraph_t next();
  };
}

#endif // _CCHECK_NAIVE_DFS_GENERATOR_HPP_
