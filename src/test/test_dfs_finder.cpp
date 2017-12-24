
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
#include "gmgf/matrix_state_initr.hpp"
#include "gmgf/matrix_opt_state_initr.hpp"

#include "gmgf/dfs_finder.hpp"

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
  graph_config* config = new graph_config(14, 3);
  graph_initr* ginitr =
    new basic_graph_initr(config);
    //new cycle_graph_initr(config);
    //new stree_graph_initr(config);

  state_initr* sinitr =
    new basic_state_initr();
    //new minmax_state_initr();
    //new matrix_state_initr();
    //new matrix_opt_state_initr();
  dfs_finder* finder = new dfs_finder(ginitr, sinitr);

  clock_t begin = clock();
  igraph_t graph = finder->next();
  clock_t end = clock();
  double cpu_time = double(end - begin) / CLOCKS_PER_SEC;

  cout << "found sspl: " << sspl(&graph) << endl
       << "lower sspl: " << config->sspl_lb() << endl
       << "elapsed time   : " << cpu_time << endl
       << "extracted nodes: " << finder->extracted_nodes() << endl;

  igraph_destroy(&graph);
  delete finder;
  delete sinitr;
  delete ginitr;
  delete config;

  return 0;
}

