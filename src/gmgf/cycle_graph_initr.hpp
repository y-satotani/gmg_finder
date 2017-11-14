
#ifndef _GMGF_CYCLE_GRAPH_INITIALIZER_HPP_
#define _GMGF_CYCLE_GRAPH_INITIALIZER_HPP_

#include <vector>
#include "basic_graph_initr.hpp"

namespace gmgf {

  /**
   * \brief 閉路を含む初期グラフを与えるグラフ初期化子．
   *
   * このグラフ初期化子で構築される初期グラフは，次の特徴を持つ．
   * - 頂点番号{1,...,d}の頂点は，0と隣接する．
   * - 頂点番号{d+1,...,n-R}の頂点は，頂点番号をvとすると，
   *   (v - gmgf::n_vert_btree(depth-1, d)) / (d-1) +
   *   gmgf::n_vert_btree(depth-2, d) と隣接する．
   *   - ただし，depth = gmgf::tree_depth (v, d) とする．
   * - 三つの頂点を定め，pとr，qとrを隣接させる．
   *   - p = gmgf::n_vert_btree (Q-1, d)
   *   - q = p + (gmgf::n_vert_btree (Q, d) - gmgf::n_vert_btree(Q-1, d)) / d
   *   - r = n - R
   *
   * \image html initial-tree-cycle-example.svg "閉路を含む初期グラフの例"
   * \image latex initial-tree-cycle-example.pdf "閉路を含む初期グラフの例"
   *
   * ちなみに， gmgf::cycle_graph_initr::possible_edges() が計算する候補辺は
   * 並びが悪く，探索時に無駄になるので， gmgf::sorted_graph_initr
   * で辺の並びをソートすることを推奨する．
   *
   */
  class cycle_graph_initr : public basic_graph_initr {
  private:
    vertex_t p();
    vertex_t q();
    vertex_t r();
  public:
    /** \copydoc basic_graph_initr::basic_graph_initr */
    cycle_graph_initr(graph_config* config);
    /** \copydoc basic_graph_initr::~basic_graph_initr */
    virtual ~cycle_graph_initr() {}

    std::vector<edge_t> initial_edges();
    std::vector<edge_t> possible_edges();
  };
}

#endif // _GMGF_CYCLE_GRAPH_INITIALIZER_HPP_
