
#ifndef _GMGF_DISTANCE_UPDATE_HPP_
#define _GMGF_DISTANCE_UPDATE_HPP_

extern "C" {
#include <igraph.h>
}

namespace gmgf {

  void update_distance_on_insert(igraph_matrix_t* Dnext,
                                 igraph_matrix_t* Snext,
                                 igraph_matrix_t* D,
                                 igraph_matrix_t* S,
                                 igraph_integer_t u,
                                 igraph_integer_t v);

  void update_distance_on_delete(igraph_matrix_t* Dnext,
                                 igraph_matrix_t* Snext,
                                 igraph_matrix_t* D,
                                 igraph_matrix_t* S,
                                 igraph_integer_t u,
                                 igraph_integer_t v);

  void set_distance_matrix_with_path_num(igraph_matrix_t* D,
                                         igraph_matrix_t* S,
                                         igraph_t* G);

}

#endif // _GMGF_DISTANCE_UPDATE_HPP_
