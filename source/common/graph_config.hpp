
#ifndef _CCHECK_GRAPH_CONFIG_HPP_
#define _CCHECK_GRAPH_CONFIG_HPP_

extern "C" {
#include <igraph.h>
}
#include <utility>
#include <vector>

namespace ccheck {

  typedef unsigned int vertex_t;
  typedef std::pair<vertex_t, vertex_t> edge_t;

  class graph_config {
  private:
    unsigned int _n;
    unsigned int _d;
  public:
    graph_config(unsigned int n, unsigned int d);
    // basic properties
    unsigned int n();
    unsigned int d();
    unsigned int k();
    unsigned int Q();
    unsigned int R();
    // lower bound of sum of shortest path length
    std::size_t sspl_lb();
    // build base graph
    vertex_t parent_of(vertex_t v);
    std::vector<vertex_t> tree_vertices();
    std::vector<edge_t> tree_edges();
    std::vector<vertex_t> leaf_vertices();
    std::vector<edge_t> leaf_edges();
    igraph_t build_tree();
  };

  // depth of vertex in tree (root = 0)
  unsigned int tree_depth(int vid, unsigned int degree);

  // the number of vertices of balanced tree (R = 0)
  unsigned int n_vert_btree(unsigned int depth, unsigned int degree);

} // end of ccheck

#endif // _CCHECK_GRAPH_CONFIG_HPP_
