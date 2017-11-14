
#ifndef _GMGF_DFS_FINDER_HPP_
#define _GMGF_DFS_FINDER_HPP_

extern "C" {
#include <igraph.h>
}
#include <utility>
#include <vector>
#include "graph_initr.hpp"
#include "state_initr.hpp"

namespace gmgf {

  /**
   * \brief 深さ優先探索により一般化ムーアグラフを探索する．
   */
  class dfs_finder {
  private:
    state_initr* m_sinitr;
    graph_initr* m_ginitr;
    std::vector<std::pair<std::size_t, state*> > m_stack;
    std::vector<edge_t> m_e_possible;
    std::vector<std::pair<std::size_t, std::size_t> > m_v_range;
    unsigned long long m_extracted_nodes;

  public:
    /**
     * \brief グラフ初期化子と状態初期化子の組で初期化する．
     * \param ginitr グラフ初期化子
     * \param sinitr 状態初期化子
     */
    dfs_finder(graph_initr* ginitr, state_initr* sinitr);

    /**
     * \brief デストラクタ．
     *
     * このとき，初期化時に渡したグラフ初期化子と状態初期化子は
     * 破棄されない．
     */
    ~dfs_finder();

    /**
     * \brief 呼び出されるまでに展開された状態数を返す．
     * \return 展開状態数
     */
    unsigned long long extracted_nodes();

    /**
     * \brief 初期化時の状態に戻す．
     */
    void reset();

    /**
     * \brief 次の一般化ムーアグラフを探索する．
     * \return 一般化ムーアグラフ
     * (もし存在しなければ，頂点数0のグラフを返す．)
     */
    igraph_t next();

  };
}

#endif // _GMGF_DFS_FINDER_HPP_
