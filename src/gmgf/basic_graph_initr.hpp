
#ifndef _GMGF_BASIC_GRAPH_INITIALIZER_HPP_
#define _GMGF_BASIC_GRAPH_INITIALIZER_HPP_

extern "C" {
#include <igraph.h>
}
#include <utility>
#include <vector>
#include "graph_initr.hpp"

namespace gmgf {

  /**
   * \brief 基本的なグラフ初期化子．
   *
   * このグラフ初期化子で構築される初期グラフは，次の特徴を持つ．
   * - 頂点番号0の頂点は，\{1,\ldots,d\}の\f$d\f$個の頂点と隣接する．
   * - 頂点番号
   */
  class basic_graph_initr : public graph_initr {
  public:
    basic_graph_initr(graph_config* config);
    virtual ~basic_graph_initr() {}

  private:
    vertex_t parent_of(vertex_t v);
    std::vector<vertex_t> initial_vertices();
    std::vector<vertex_t> possible_vertices();

  public:
    virtual std::vector<edge_t> initial_edges();
    virtual std::vector<edge_t> possible_edges();
  };

} // end of gmgf

#endif // _GMGF_BASIC_GRAPH_INITIALIZER_HPP_
