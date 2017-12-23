
#ifndef _GMGF_FBS_ENUMER_HPP_
#define _GMGF_FBS_ENUMER_HPP_

extern "C" {
#include <igraph.h>
}
#include <vector>
#include "graph_initr.hpp"
#include "state_initr.hpp"

namespace gmgf {

  /**
   * \brief フロンティア法に基づき一般化ムーアグラフを列挙する．
   */
  class fbs_enumer {
  private:
    state_initr* m_sinitr;
    graph_initr* m_ginitr;
    std::vector<edge_t> m_e_possible;
    std::vector<std::pair<std::size_t, std::size_t> > m_v_range;
    unsigned long long m_extracted_states;

  public:
    /**
     * \brief グラフ初期化子と状態初期化子の組で初期化する．
     * \param ginitr グラフ初期化子
     * \param sinitr 状態初期化子
     */
    fbs_enumer(graph_initr* ginitr, state_initr* sinitr);

    /**
     * \brief 呼び出されるまでに展開された状態数を返す．
     * \return 展開状態数
     */
    unsigned long long extracted_states();

    /**
     * \brief 一般化ムーアグラフを列挙する．
     * \return 一般化ムーアグラフのリスト
     */
    std::vector<igraph_t> enumerate();

  };
}

#endif // _GMGF_FBS_ENUMER_HPP_
