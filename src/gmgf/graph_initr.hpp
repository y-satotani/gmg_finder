
#ifndef _GMGF_GRAPH_INITR_HPP_
#define _GMGF_GRAPH_INITR_HPP_

extern "C" {
#include <igraph.h>
}
#include <utility>
#include <vector>
#include "graph_config.hpp"

namespace gmgf {

  /**
   * \brief 探索の初期グラフを生成するグラフ初期化子．
   */
  class graph_initr {
  protected:
    /** \brief 生成する初期グラフの設定 */
    graph_config* m_config;

  public:
    /**
     * \brief コンストラクタ．
     * \param config 生成するグラフの設定
     */
    graph_initr(graph_config* config);

    /**
     * \brief デストラクタ．
     *
     * このとき，初期化時に渡したグラフの設定は破棄されない．　
     */
    virtual ~graph_initr() {}

    /**
     * \brief 生成する初期グラフの設定を返す．
     * \return グラフの設定
     */
    graph_config* get_config();

#if 0
    virtual vertex_t parent_of(vertex_t v) = 0;

    /**
     * \brief 初期グラフに含まれる辺と接する頂点のリストを求める．
     * \return 頂点リスト
     */
    virtual std::vector<vertex_t> initial_vertices() = 0;

    /**
     * \brief 探索の候補となる辺と接する頂点のリストを求める．
     * \return 頂点リスト
     */
    virtual std::vector<vertex_t> possible_vertices() = 0;
#endif

    /**
     * \brief 初期グラフに含まれる辺のリストを求める．
     * \return 辺リスト
     */
    virtual std::vector<edge_t> initial_edges() = 0;

    /**
     * \brief 探索の候補となる辺のリストを求める．
     * \return 辺リスト
     */
    virtual std::vector<edge_t> possible_edges() = 0;

    /**
     * \brief フロンティアを計算する．
     *
     * フロンティアとは，与えられた候補辺リスト\f$\{e_i\}\f$と
     * ある頂点\f$v\f$に対して，\f$v\f$と\f$e_i\f$が接する\f$i\f$の最小値
     * と最大値の組である．
     * \return 頂点番号に対するフロンティア
     */
    std::vector<std::pair<std::size_t, std::size_t> > vertex_frontier();

    /**
     * \brief 初期グラフに含まれる辺のリストから，初期グラフを構築する．
     * \return 初期グラフ
     */
    igraph_t build();
  };

} // end of gmgf

#endif // _GMGF_GRAPH_INITR_HPP_
