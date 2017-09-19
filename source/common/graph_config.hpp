
#ifndef _CCHECK_GRAPH_CONFIG_HPP_
#define _CCHECK_GRAPH_CONFIG_HPP_

#include <igraph.h>

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
    unsigned int Q();
    unsigned int R();
  };

} // end of ccheck

#endif // _CCHECK_GRAPH_CONFIG_HPP_
