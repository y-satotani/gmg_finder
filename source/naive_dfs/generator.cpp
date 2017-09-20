
#include "generator.hpp"
#include <iostream>

using namespace ccheck;

namespace ccheck {

  bool dfs_generator::
  degree_constraint(std::size_t ei, igraph_t* G, bool add) {
    return false;
  }

  bool dfs_generator::
  cycle_constraint(std::size_t ei, igraph_t* G, bool add) {
    return false;
  }

  dfs_generator::dfs_generator() {

  }

  dfs_generator::dfs_generator(const graph_config& conf) {
    m_config = conf;
    m_edges = m_config.leaf_edges();
    m_vert_range.clear();
    for(size_t vi = 0; vi < m_config.n(); vi++) {
      std::pair<int, int> p(-1, -1);
      for(size_t ei = 0; ei < m_edges.size(); ei++) {
        if(m_edges[ei].first == vi || m_edges[ei].second == vi) {
          if(p.first < 0) p.first = ei;
          p.second = ei;
        }
      }
    }
    reset();
  }

  dfs_generator::~dfs_generator() {
    for(std::size_t i = 0; i < m_stack.size(); i++)
      igraph_destroy(&m_stack[i].second);
  }

  void dfs_generator::reset() {
    for(std::size_t i = 0; i < m_stack.size(); i++)
      igraph_destroy(&m_stack[i].second);
    m_stack.clear();
    m_stack.push_back(dfs_node_t(0, m_config.build_tree()));
  }

  igraph_t dfs_generator::next() {
    std::vector<edge_t> edges = m_config.leaf_edges();

    while(m_stack.size() > 0) {
      dfs_node_t node = m_stack.back();
      std::size_t ei = node.first;
      igraph_t G = node.second;
      m_stack.pop_back();

      if(ei == edges.size()) {
        return G;
      }

      igraph_t H;
      igraph_copy(&H, &G);
      if(degree_constraint(ei, &H, false) &&
         cycle_constraint(ei, &H, false)) {
        m_stack.push_back(dfs_node_t(ei, H));
      } else {
        igraph_destroy(&H);
      }

      igraph_copy(&H, &G);
      //igraph_add_edge(&H, u, v);
      if(degree_constraint(ei, &H, true) &&
         cycle_constraint(ei, &H, true)) {
        m_stack.push_back(dfs_node_t(ei, H));
      } else {
        igraph_destroy(&H);
      }

      igraph_destroy(&G);
    }

    igraph_t dummy;
    igraph_empty(&dummy, 0, IGRAPH_UNDIRECTED);
    return dummy;
  }

}
