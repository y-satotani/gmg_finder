
#ifndef _CCHECK_GRAPH_CONFIG_TCONJ_HPP_
#define _CCHECK_GRAPH_CONFIG_TCONJ_HPP_

#include <vector>
#include "graph_config.hpp"

namespace ccheck {

  class graph_config_r2 : public graph_config {
  private:
  public:
    graph_config_r2(std::size_t n, std::size_t d);
    virtual ~graph_config_r2() {}
    std::vector<edge_t> tree_edges();
    std::vector<edge_t> leaf_edges();
  };
}

#endif // _CCHECK_GRAPH_CONFIG_TCONJ_HPP_
