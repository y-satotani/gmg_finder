
#ifndef _GMGF_BASIC_STATE_BUILDER_HPP_
#define _GMGF_BASIC_STATE_BUILDER_HPP_

#include "state_initr.hpp"
#include "state.hpp"
#include "basic_state.hpp"
#include "basic_graph_initr.hpp"

namespace gmgf {

  class basic_state_initr : public state_initr {
  public:
    virtual ~basic_state_initr() {};

    virtual state* initial(graph_initr* ginitr);
  };

}

#endif // _GMGF_BASIC_STATE_BUILDER_HPP_
