
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
   * - 頂点番号{1,...,d}の頂点は，0と隣接する．
   * - 頂点番号{d+1,...,n-R}の頂点は，頂点番号をvとすると，
   *   (v - gmgf::n_vert_btree(depth-1, d)) / (d-1) +
   *   gmgf::n_vert_btree(depth-2, d) と隣接する．
   *   - ただし，depth = gmgf::tree_depth (v, d) とする．
   *
   * \image html initial-tree-example.svg "基本初期グラフの例"
   * \image latex initial-tree-example.pdf "基本初期グラフの例"
   */
  class basic_graph_initr : public graph_initr {
  public:
    /** \copydoc graph_initr::graph_initr */
    basic_graph_initr(graph_config* config);
    /** \copydoc graph_initr::~graph_initr */
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
