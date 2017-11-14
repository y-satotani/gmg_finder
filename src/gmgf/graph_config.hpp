/** \file graph_config.hpp */

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
   * 頂点に関する量やムーアグラフと比べたときの頂点数の差，
   * 一般化ムーアグラフの頂点間距離の総和を計算する．
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

    /** \brief 設定した頂点数を返す． \return 頂点数 */
    unsigned int n();

    /** \brief 設定した次数を返す． \return 次数 */
    unsigned int d();

    /**
     * \brief 一般化ムーアグラフの直径に関する量を計算する．
     *
     * 次の式で計算される．
     * \f[ k = \max\{l | n-1-\sum_{i=1}^{l-1}d(d-1)^{i-1} \geq 0\} \f]
     * \return \f$k\f$
     */
    unsigned int k();

    /**
     * \brief 一般化ムーアグラフの直径に関する量を計算する．
     *
     * 次の式で計算される．
     * \f[ Q = \max\{q | n-1-\sum_{i=1}^{q}d(d-1)^{i-1} \geq 0\} \f]
     * \return \f$Q\f$
     */
    unsigned int Q();

    /**
     * \brief ムーアグラフの頂点数との比較に関する量を計算する．
     *
     * 次の式で計算される．
     * \f[ R = n - 1 - \sum_{i=1}^{Q(n,d)}d(d-1)^{i-1} \f]
     * \return \f$R\f$
     */
    unsigned int R();

    /**
     * \brief 頂点間距離の総和の下界を計算する．
     *
     * 一般化ムーアグラフの頂点間距離の総和を次の式で計算する．
     * \f[ S = n\left[\sum^{Q}_{i=1}id(d-1)^{i-1}+(Q+1)R\right] \f]
     *
     * なお，平均頂点間距離を計算したい場合は，
     * \f[ P = \frac{S}{n(n-1)} \f]
     * とすればよい．
     * \return 頂点間距離の総和の下界
     */
    unsigned int sspl_lb();
  };

  /**
   * \brief 次数dの平衡木における頂点vの深さを求める．
   *
   * 次の式で計算される．
   * \f{align*}{
   *   & 0 &\:& v = 0 \\
   *   & \mbox{log}_{d-1}{\left(\frac{(v-1)(d-2)}{d}+1\right)}
   *     + 1 &\:& v > 0
   * \f}
   *
   * \param vid 頂点番号
   * \param degree 次数
   * \return 頂点の深さ
   */
  unsigned int tree_depth(int vid, unsigned int degree);

  /**
   * \brief 深さと次数から平衡木の頂点数を求める．
   *
   * 次の式で計算される．
   * \f{align*}{
   *   & 1 &\:& \mbox{dep} = 0 \\
   *   & \mbox{deg}+1 &\:& \mbox{dep} = 1 \\
   *   & \frac{\mbox{deg}\left((\mbox{deg}-1)^{\mbox{dep}}-1\right)}
   *     {\mbox{deg}-2}+1 &\:& \mbox{dep} > 1
   * \f}
   * \param depth 木の深さ(0:根のみ)
   * \param degree 次数
   * \return 頂点数
   */
  unsigned int n_vert_btree(unsigned int depth, unsigned int degree);

} // end of gmgf

#endif // _GMGF_GRAPH_CONFIG_HPP_
