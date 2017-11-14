
#ifndef _GMGF_STATE_BUILDER_HPP_
#define _GMGF_STATE_BUILDER_HPP_

#include "state.hpp"
#include "graph_initr.hpp"

namespace gmgf {

  /**
   * \brief 探索の初期状態を与える状態初期化子
   */
  class state_initr {
  public:
    /**
     * \brief デストラクタ
     */
    virtual ~state_initr() {};

    /**
     * \brief グラフ初期化子から，そのグラフの初期状態を生成する．
     * \param ginitr グラフ初期化子
     * \return 初期状態
     */
    virtual state* initial(graph_initr* ginitr) = 0;
  };
}

#endif // _GMGF_STATE_BUILDER_HPP_
