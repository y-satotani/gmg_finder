
extern "C" {
#include <igraph.h>
}
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include "gmgf/distance_update.hpp"

using namespace std;
using namespace gmgf;

char graph_random[] = "random", graph_scale_free[] = "scale-free";

void make_distance_matrix_only(igraph_matrix_t* D,
                               igraph_t* G) {
  igraph_matrix_init(D, igraph_vcount(G), igraph_vcount(G));
  igraph_shortest_paths(G, D, igraph_vss_all(), igraph_vss_all(),
                        IGRAPH_ALL);
}

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
  if(argc < 5) {
    cout << "usage : " << argv[0]
         << " (random|scale-free) n (p|m) seed" << endl;
    cout << "output: n,p-or-m,type,seed,m,test,time-igraph,time" << endl;
    return 1;
  }
  unsigned long seed = strtoul(argv[4], NULL, 0);
  igraph_rng_seed(igraph_rng_default(), seed);

  igraph_t G;
  char* graph_type = argv[1];
  igraph_integer_t n = atoi(argv[2]);
  igraph_real_t p_or_m;
  if(strcmp(graph_type, graph_random) == 0) {
    p_or_m = atof(argv[3]);
    igraph_erdos_renyi_game(&G, IGRAPH_ERDOS_RENYI_GNP,
                            n, p_or_m, 0, 0);
  } else {
    p_or_m = atoi(argv[3]);
    igraph_barabasi_game(&G, n, 1, (igraph_integer_t)p_or_m,
                         0, 0, 1, 0, IGRAPH_BARABASI_BAG, 0);
  }

  igraph_matrix_t D, S, Dtrain;
  clock_t start, end;
  double time_igraph, time;
  igraph_matrix_init(&D, n, n);
  igraph_matrix_init(&S, n, n);
  set_distance_matrix_with_path_num(&D, &S, &G);

  igraph_matrix_t Dnew, Snew;
  igraph_matrix_init(&Dnew, n, n);
  igraph_matrix_init(&Snew, n, n);

  igraph_integer_t eid = igraph_rng_get_integer
    (igraph_rng_default(), 0, igraph_ecount(&G)-1);
  igraph_integer_t u, v;
  igraph_edge(&G, eid, &u, &v);
  igraph_delete_edges(&G, igraph_ess_1(eid));

  start = clock();
  make_distance_matrix_only(&Dtrain, &G);
  end = clock();
  time_igraph = double(end - start) / CLOCKS_PER_SEC;

  start = clock();
  update_distance_on_delete(&Dnew, &Snew, &D, &S, u, v);
  end = clock();
  time = double(end - start) / CLOCKS_PER_SEC;

  igraph_bool_t test = igraph_matrix_all_e(&Dnew, &Dtrain);

  cout << n << "," << p_or_m << "," << graph_type << "," << seed << ","
       << igraph_ecount(&G) << "," << test << ","
       << time_igraph << "," << time << endl;

  igraph_matrix_destroy(&Dnew);
  igraph_matrix_destroy(&Snew);
  igraph_matrix_destroy(&Dtrain);
  igraph_matrix_destroy(&D);
  igraph_matrix_destroy(&S);
  igraph_destroy(&G);

  return 0;
}
