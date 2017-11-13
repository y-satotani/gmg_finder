/** \file graph_config.cpp */
#include "graph_config.hpp"
#include <cmath>

namespace gmgf {

  graph_config::graph_config(unsigned int n, unsigned int d) {
    _n = n;
    _d = d;
  }

  unsigned int graph_config::n() {
    return _n;
  }

  unsigned int graph_config::d() {
    return _d;
  }

  unsigned int graph_config::k() {
    unsigned int depth = tree_depth(_n-1, _d);
    if(_n == n_vert_btree(depth, _d))
      return depth + 1;
    else
      return depth;
  }

  unsigned int graph_config::Q() {
    return k() - 1;
  }

  unsigned int graph_config::R() {
    return _n - n_vert_btree(k() - 1, _d);
  }

  std::size_t graph_config::sspl_lb() {
    std::size_t sspl = 0;
    for(std::size_t j = 1; j < k(); j++)
      sspl += j * _d * (std::size_t)pow(_d - 1, j - 1);
    sspl = n() * (sspl + k() * R());
    return sspl;
  }

  unsigned int tree_depth(int v, unsigned int d) {
    if(v <= 0)
      return 0;
    else
      return (unsigned int)(log((v-1.)*(d-2.)/d+1) / log(d-1)) + 1;
  }

  unsigned int n_vert_btree(unsigned int dep, unsigned int deg) {
    if(dep == 0)
      return 1;
    else if(dep == 1)
      return deg + 1;
    else
      return (unsigned int)(deg * (pow(deg-1, dep) - 1)) / (deg - 2) + 1;
  }

}
