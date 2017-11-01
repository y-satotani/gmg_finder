
extern "C" {
#include <igraph.h>
}
#include <cassert>
#include <ctime>
#include <iostream>
#include "gmgf/distance_update.hpp"

using namespace std;
using namespace gmgf;

void igraph_complement(igraph_t* to, igraph_t* from) {
  igraph_integer_t u, v;
  igraph_empty(to, igraph_vcount(from), IGRAPH_UNDIRECTED);
  for(u = 0; u < igraph_vcount(from); u++) {
    for(v = 0; v < igraph_vcount(from); v++) {
      if(u >= v) continue;
      igraph_integer_t eid;
      igraph_get_eid(from, &eid, u, v, 0, 0);
      if(eid < 0)
        igraph_add_edge(to, u, v);
    }
  }
}

void print_matrix(igraph_matrix_t* M) {
  int row, col;
  for(row = 0; row < igraph_matrix_nrow(M); row++) {
    for(col = 0; col < igraph_matrix_ncol(M); col++) {
      cout << igraph_matrix_e(M, row, col) << " ";
    }
    cout << endl;
  }
}

int main(int argc, char* argv[]) {
  igraph_rng_seed(igraph_rng_default(), time(NULL));

  igraph_t G;
  igraph_integer_t n = 100;
  igraph_full(&G, n, 0, 0);

  igraph_matrix_t D, Dnew, Dtrain;
  igraph_matrix_t S, Snew, Strain;

  igraph_matrix_init(&D, n, n);
  igraph_matrix_init(&S, n, n);
  igraph_matrix_init(&Dnew, n, n);
  igraph_matrix_init(&Snew, n, n);
  igraph_matrix_init(&Dtrain, n, n);
  igraph_matrix_init(&Strain, n, n);

  set_distance_matrix_with_path_num(&D, &S, &G);

  while(igraph_ecount(&G) > 0) {
    igraph_integer_t eid = igraph_rng_get_integer
      (igraph_rng_default(), 0, igraph_ecount(&G)-1);
    igraph_integer_t u, v;
    igraph_edge(&G, eid, &u, &v);
    igraph_delete_edges(&G, igraph_ess_1(eid));

    update_distance_on_delete(&Dnew, &Snew, &D, &S, u, v);
    set_distance_matrix_with_path_num(&Dtrain, &Strain, &G);
    igraph_matrix_update(&D, &Dnew);
    igraph_matrix_update(&S, &Snew);

    assert(igraph_matrix_all_e(&Dnew, &Dtrain) &&
           igraph_matrix_all_e(&Snew, &Strain));
  }

  igraph_matrix_destroy(&Dtrain);
  igraph_matrix_destroy(&Strain);
  igraph_matrix_destroy(&Dnew);
  igraph_matrix_destroy(&Snew);
  igraph_matrix_destroy(&D);
  igraph_matrix_destroy(&S);
  igraph_destroy(&G);

  return 0;
}
