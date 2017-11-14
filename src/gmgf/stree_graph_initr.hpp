
#ifndef _GMGF_STREE_GRAPH_INITIALIZER_HPP_
#define _GMGF_STREE_GRAPH_INITIALIZER_HPP_

#include <vector>
#include "graph_initr.hpp"

namespace gmgf {

  /**
   * \brief 全域木を初期グラフとして与えるグラフ初期化子．
   *
   * このグラフ初期化子で構築される全域木は，次の特徴を持つ．
   * - 頂点番号{1,...,d}の頂点は，0と隣接する．
   * - 頂点番号{d+1,...,n-R}の頂点は，その頂点番号をvとすると，
   * (v - gmgf::n_vert_btree (depth-1, d)) mod n_vert_layer +
   * gmgf::n_vert_btree (depth-2, d)
   * と隣接する．
   *   - ただし，
   *     - depth = gmgf::tree_depth (v, d)
   *     - n_vert_layer =
   *       gmgf::n_vert_btree (depth-1, d) - gmgf::n_vert_btree (depth-2, d)
   *
   *     とする．
   *
   * \image html initial-spanning-tree-12-example.svg "初期全域木の例(n=12,d=3)"
   * \image latex initial-spanning-tree-12-example.pdf "初期全域木の例(n=12,d=3)"
   *
   * \image html initial-spanning-tree-18-example.svg "初期全域木の例(n=18,d=3)"
   * \image latex initial-spanning-tree-18-example.pdf "初期全域木の例(n=18,d=3)"
   *
   */
  class stree_graph_initr : public graph_initr {
  private:
    vertex_t parent_of(vertex_t v);
    std::vector<vertex_t> initial_vertices();
    std::vector<vertex_t> possible_vertices();

  public:
    /** \copydoc graph_initr::graph_initr */
    stree_graph_initr(graph_config* config);
    /** \copydoc graph_initr::~graph_initr */
    virtual ~stree_graph_initr() {}

    std::vector<edge_t> initial_edges();
    std::vector<edge_t> possible_edges();
  };
}

#endif // _GMGF_STREE_GRAPH_INITIALIZER_HPP_
