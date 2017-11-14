
#ifndef _GMGF_INIT_BUILDER_SORTER_HPP_
#define _GMGF_INIT_BUILDER_SORTER_HPP_

extern "C" {
#include <igraph.h>
}
#include <utility>
#include <vector>
#include "graph_initr.hpp"

namespace gmgf {

  /**
   * \brief あるグラフ初期化子の候補辺リストをソートして返すグラフ初期化子．
   *
   * あるグラフ初期化子に対して，その候補辺リストを次の規則で並べ替える．
   * -# 各頂点\f$v\f$に対して，候補辺リストにおける出現回数を求める．
   * -# 出現回数がもっとも小さい頂点と接続する辺を取り出し，
   * 新たな候補辺リストに加える．
   * -# 元の候補辺リストが空になるまで繰り返す．
   */
  class sorted_graph_initr : public graph_initr {
  private:
    graph_initr* m_builder;

  public:
    /**
     * \brief コンストラクタ．
     * \param builder ソート対象のグラフ初期化子
     */
    sorted_graph_initr(graph_initr* builder);

    /**
     * デストラクタ．
     * このとき，初期化時に渡したグラフ初期化子は破棄されない．　
     */
    virtual ~sorted_graph_initr() {}

    std::vector<edge_t> initial_edges();
    std::vector<edge_t> possible_edges();
  };

} // end of gmgf

#endif // _GMGF_INIT_BUILDER_SORTER_HPP_
