
#ifndef _GMGF_STATE_BUILDER_HPP_
#define _GMGF_STATE_BUILDER_HPP_

#include "state.hpp"
#include "graph_initr.hpp"

namespace gmgf {

  class state_initr {
  public:
    virtual ~state_initr() {};
    virtual state* initial(graph_initr* ginitr) = 0;
  };
}

#endif // _GMGF_STATE_BUILDER_HPP_
