
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
    unsigned long long m_extracted_nodes;

  protected:
    bool is_valid_change_degree(std::size_t ei, igraph_t* G, bool add);
    bool is_valid_change_cycle(std::size_t ei, igraph_t* G, bool add);
    bool is_valid_graph_degree(igraph_t* G);
    bool is_valid_graph_diameter(igraph_t* G);
    bool is_valid_change(std::size_t ei, igraph_t* G, bool add);
    bool is_valid_graph(igraph_t* G);
  public:
    dfs_generator(graph_config* conf);
    ~dfs_generator();
    void reset();
    igraph_t next();
    unsigned long long extracted_nodes();
  };
}

#endif // _CCHECK_NAIVE_DFS_GENERATOR_HPP_
