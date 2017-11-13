
#ifndef _GMGF_MMMTR_STATE_BUILDER_HPP_
#define _GMGF_MMMTR_STATE_BUILDER_HPP_

extern "C" {
#include <igraph.h>
}
#include <utility>
#include "state_initr.hpp"

namespace gmgf {

  class mmmtr_state_initr : public state_initr {
  public:
    virtual ~mmmtr_state_initr() {};
    virtual state* initial(graph_initr* ginitr);
  };

}

#endif // _GMGF_MMMTR_STATE_BUILDER_HPP_
