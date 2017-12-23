
extern "C" {
#include <igraph.h>
}
#include <iostream>
#include <ctime>

#include "gmgf/graph_config.hpp"

#include "gmgf/graph_initr.hpp"
#include "gmgf/basic_graph_initr.hpp"
#include "gmgf/cycle_graph_initr.hpp"
#include "gmgf/stree_graph_initr.hpp"

#include "gmgf/state_initr.hpp"
#include "gmgf/basic_state_initr.hpp"
#include "gmgf/minmax_state_initr.hpp"
#include "gmgf/mmmtr_state_initr.hpp"

#include "gmgf/fbs_enumer.hpp"

using namespace std;
using namespace gmgf;

int sspl(igraph_t* G) {
  igraph_matrix_t path;
  int sspl;
  igraph_matrix_init(&path,
                     igraph_vcount(G), igraph_vcount(G));
  igraph_shortest_paths(G, &path,
                        igraph_vss_all(), igraph_vss_all(),
                        IGRAPH_ALL);
  sspl = (int) igraph_matrix_sum(&path);
  igraph_matrix_destroy(&path);
  return sspl;
}

int main(int argc, char* argv[]) {

  // testing specific graph configuration
  graph_config* config = new graph_config(16, 3);
  graph_initr* ginitr =
    new basic_graph_initr(config);
    //new cycle_graph_initr(config);
    //new stree_graph_initr(config);

  state_initr* sinitr =
    new basic_state_initr();
    //new minmax_state_initr();
    //new mmmtr_state_initr();
  fbs_enumer* enumer = new fbs_enumer(ginitr, sinitr);

  clock_t begin = clock();
  vector<igraph_t> graphs = enumer->enumerate();
  clock_t end = clock();
  double cpu_time = double(end - begin) / CLOCKS_PER_SEC;

  cout << "# of graphs: " << graphs.size() << endl
       << "elapsed time   : " << cpu_time << endl
       << "extracted nodes: " << enumer->extracted_states() << endl;

  for(size_t gi = 0; gi < graphs.size(); gi++)
    igraph_destroy(&graphs[gi]);
  delete enumer;
  delete sinitr;
  delete ginitr;
  delete config;

  return 0;
}

