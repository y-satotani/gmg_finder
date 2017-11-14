
#ifndef _GMGF_BASIC_STATE_BUILDER_HPP_
#define _GMGF_BASIC_STATE_BUILDER_HPP_

#include "state_initr.hpp"

namespace gmgf {

  /**
   * \brief gmgf::basic_state に対する状態初期化子
   */
  class basic_state_initr : public state_initr {
  public:
    /** \copydoc gmgf::state_initr::~state_initr */
    virtual ~basic_state_initr() {};

    /**
     * \brief グラフ初期化子から， gmgf::basic_state 型の初期状態を生成する．
     * \param ginitr グラフ初期化子
     * \return gmgf::basic_state 型の初期状態
     */
    state* initial(graph_initr* ginitr);
  };

}

#endif // _GMGF_BASIC_STATE_BUILDER_HPP_
