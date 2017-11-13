/** \file graph_config.hpp
 * \brief 一般化ムーアグラフに関する基礎的な量を計算する．
 */
#ifndef _GMGF_GRAPH_CONFIG_HPP_
#define _GMGF_GRAPH_CONFIG_HPP_

extern "C" {
#include <igraph.h>
}
#include <utility>
#include <vector>

namespace gmgf {

  /** \brief 頂点タイプ */
  typedef unsigned int vertex_t;
  /** \brief 辺タイプ */
  typedef std::pair<vertex_t, vertex_t> edge_t;

  /**
   * \brief 一般化ムーアグラフに関する基礎的な量を計算する．
   *
   * 頂点数などなど
   */
  class graph_config {
  private:
    unsigned int _n;
    unsigned int _d;
  public:
    /**
     * \brief 指定された頂点数と次数で初期化する．
     * \param n 頂点数
     * \param d 次数
     */
    graph_config(unsigned int n, unsigned int d);
    virtual ~graph_config() {}
    /** \brief 設定した頂点数を返す． \return 頂点数 */
    unsigned int n();

    /** \brief 設定した次数を返す． \return 次数 */
    unsigned int d();

    /**
     * \brief 一般化ムーアグラフの直径を計算する．
     *
     * 次の式で計算される．
     * \f[ k = 1 \f]
     * \return 直径
     */
    unsigned int k();

    /**
     * \brief 一般化ムーアグラフの直径を計算する．
     *
     * 次の式で計算される．
     * \return 直径
     */
    unsigned int Q();

    /**
     * \brief 一般化ムーアグラフのパラメータ
     *
     * \return パラメータ
     */
    unsigned int R();

    /**
     * \brief 頂点間距離の総和の下界を計算する．
     *
     * \f[ S = \sum_{(s,t)\in V\times V} \f]
     */
    std::size_t sspl_lb();
  };

  /**
   * \brief 木における頂点の深さを求める．
   *
   * 根は0と数える．
   * \param vid 頂点番号
   * \param degree 次数
   * \return 頂点の深さ
   */
  unsigned int tree_depth(int vid, unsigned int degree);

  /**
   * \brief 木の頂点数を求める．
   *
   * \param depth 木の深さ(0:根のみ)
   * \param degree 次数
   * \return 頂点数
   */
  unsigned int n_vert_btree(unsigned int depth, unsigned int degree);

} // end of gmgf

#endif // _GMGF_GRAPH_CONFIG_HPP_
