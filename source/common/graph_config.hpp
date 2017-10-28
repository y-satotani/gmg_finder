
#ifndef _GMGF_GRAPH_CONFIG_HPP_
#define _GMGF_GRAPH_CONFIG_HPP_

extern "C" {
#include <igraph.h>
}
#include <utility>
#include <vector>

namespace gmgf {

  typedef unsigned int vertex_t;
  typedef std::pair<vertex_t, vertex_t> edge_t;

  class graph_config {
  private:
    unsigned int _n;
    unsigned int _d;
  public:
    graph_config(unsigned int n, unsigned int d);
    virtual ~graph_config() {}
    // basic properties
    unsigned int n();
    unsigned int d();
    unsigned int k();
    unsigned int Q();
    unsigned int R();
    // lower bound of sum of shortest path length
    std::size_t sspl_lb();
  };

  // depth of vertex in tree (root = 0)
  unsigned int tree_depth(int vid, unsigned int degree);

  // the number of vertices of balanced tree (R = 0)
  unsigned int n_vert_btree(unsigned int depth, unsigned int degree);

} // end of gmgf

#endif // _GMGF_GRAPH_CONFIG_HPP_
