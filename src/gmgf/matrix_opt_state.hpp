
#ifndef _GMGF_MMMTR_STATE_HPP_
#define _GMGF_MMMTR_STATE_HPP_

extern "C" {
#include <igraph.h>
}
#include <utility>
#include "basic_state.hpp"

namespace gmgf {

  /**
   * \brief 距離間距離が格納された行列を利用して，
   頂点間距離の計算の高速化を図った状態．
   */
  class matrix_opt_state : public basic_state {
  protected:
    /** \brief 最小グラフの頂点間距離を表す行列 */
    igraph_matrix_t d_min;
    /** \brief 最大グラフの頂点間距離を表す行列 */
    igraph_matrix_t d_max;
    /** \brief 最大グラフの最短経路数を表す行列 */
    igraph_matrix_t s_max;
    /** \brief 最大グラフの直径 */
    igraph_real_t diam;

  public:
    /**
     * \brief コンストラクタ
     *
     * 初期化時に渡したグラフおよび行列は igraph_destroy 関数や
     igraph_matrix_destroy 関数で破棄してはならず，
     このオブジェクトの破棄と同時に破棄される．
     * \param config 探索対象のグラフ設定
     * \param G
     * \param d_min 最小グラフの頂点間距離を表す行列
     * \param d_max 最大グラフの頂点間距離を表す行列
     * \param s_max 最大グラフの最短経路数を表す行列
     * \param diam 最大グラフの直径
     */
    matrix_opt_state(graph_config* config, igraph_t G,
                     igraph_matrix_t d_min,
                     igraph_matrix_t d_max, igraph_matrix_t s_max, igraph_real_t diam);

    /**
     * \brief コピーコンストラクタ
     *
     * オブジェクトのコピーを作成する．
     * gmgf::matrix_opt_state::matrix_opt_state
     (graph_config*, igraph_t, igraph_matrix_t, igraph_matrix_t,
     igraph_matrix_t, igraph_real_t)
     と違い，被コピーオブジェクトのグラフをディープコピーする．
     * \param s 被コピーオブジェクト
     */
    matrix_opt_state(const matrix_opt_state& s);

    /**
     * \brief デストラクタ
     *
     * このとき，初期化時に与えられたグラフおよび行列を
     igraph_destroy 関数および igraph_matrix_destroy 関数で破棄する．
     * グラフの設定は破棄しない．
     */
    virtual ~matrix_opt_state();

    virtual bool can_add_edge_cycle(edge_t e,
                                    std::vector<vertex_t> enter,
                                    std::vector<vertex_t> exit
                                    );

    virtual bool can_add_edge_diameter(edge_t e,
                                       std::vector<vertex_t> enter,
                                       std::vector<vertex_t> exit
                                       );

    virtual bool can_noadd_edge_diameter(edge_t e,
                                         std::vector<vertex_t> enter,
                                         std::vector<vertex_t> exit
                                         );

    virtual bool is_final_diameter();

    virtual void add_edge(edge_t e);
    virtual void noadd_edge(edge_t e);
    virtual state* copy();
  };

}

#endif // _GMGF_MATRIX_OPT_STATE_HPP_
