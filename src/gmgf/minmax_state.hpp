
#ifndef _GMGF_MINMAX_STATE_HPP_
#define _GMGF_MINMAX_STATE_HPP_

extern "C" {
#include <igraph.h>
}
#include <utility>
#include "basic_state.hpp"

namespace gmgf {

  /**
   * \brief 最大グラフで直径の下界を導出し，枝刈りを実現した状態．
   *
   * 最大グラフとは，未判定の辺すべてを探索中のグラフに追加した
   グラフである．例えば，
   * \image html min-graph-example.svg
   * の最大グラフは，破線で示した辺をすべて追加して，
   * \image html max-graph-example.svg
   * である．このとき，元になったグラフを最小グラフという．
   *
   * このグラフの直径が，直径の下界である．
   直径の下界が条件を満たさなければ枝刈りを行う．
   */
  class minmax_state : public basic_state {
  protected:
    /** \brief 最大グラフ */
    igraph_t H;
  public:
    /**
     * \brief コンストラクタ
     *
     * 初期化時に渡したグラフは igraph_destroy 関数で
     破棄してはならず，このオブジェクトの破棄と同時に破棄される．
     * \param config 探索対象のグラフ設定
     * \param G 最小グラフ
     * \param H 最大グラフ
     */
    minmax_state(graph_config* config, igraph_t G, igraph_t H);

    /**
     * \brief コピーコンストラクタ
     *
     * オブジェクトのコピーを作成する．
     * gmgf::minmax_state::minmax_state (graph_config*, igraph_t, igraph_t)
     と違い，被コピーオブジェクトのグラフをディープコピーする．
     * \param s 被コピーオブジェクト
     */
    minmax_state(const minmax_state& s);

    /**
     * \brief デストラクタ
     *
     * このとき，初期化時に与えられたグラフを
     igraph_destroy 関数で破棄する．
     * グラフの設定は破棄しない．
     */
    virtual ~minmax_state();

    virtual bool can_add_edge_diameter(edge_t e,
                                       std::vector<vertex_t> enter,
                                       std::vector<vertex_t> exit
                                       );

    virtual bool can_noadd_edge_diameter(edge_t e,
                                         std::vector<vertex_t> enter,
                                         std::vector<vertex_t> exit);

    virtual void noadd_edge(edge_t e);
    virtual state* copy();
  };

}

#endif // _GMGF_MINMAX_STATE_HPP_
