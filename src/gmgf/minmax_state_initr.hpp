
#ifndef _GMGF_MINMAX_STATE_BUILDER_HPP_
#define _GMGF_MINMAX_STATE_BUILDER_HPP_

extern "C" {
#include <igraph.h>
}
#include <utility>
#include "state_initr.hpp"

namespace gmgf {

  class minmax_state_initr : public state_initr {
  public:
    virtual ~minmax_state_initr() {};
    state* initial(graph_initr* ginitr);
  };

}

#endif // _GMGF_MINMAX_STATE_BUILDER_HPP_
