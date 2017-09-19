
extern "C" {
#include <igraph.h>
}

#ifndef _CCHECK_GRAPH_CONFIG_HPP_
#define _CCHECK_GRAPH_CONFIG_HPP_

namespace ccheck {

  class graph_config {
  private:
    unsigned int _n;
    unsigned int _d;
  public:
    graph_config(unsigned int n, unsigned int d);
    // basic properties
    unsigned int n();
    unsigned int d();
    unsigned int depth(int vid);
    unsigned int Q();
    unsigned int R();
    // build base graph
    igraph_t build_base_graph();
  };

} // end of ccheck

#endif // _CCHECK_GRAPH_CONFIG_HPP_
