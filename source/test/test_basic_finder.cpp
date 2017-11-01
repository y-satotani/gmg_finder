
extern "C" {
#include <igraph.h>
}
#include <iostream>
#include <ctime>

#include "gmgf/graph_config.hpp"
#include "gmgf/initial_builder.hpp"
#include "gmgf/initial_builder_cycle_conjecture.hpp"
#include "gmgf/initial_builder_stree_conjecture.hpp"

#include "gmgf/basic_state_manager.hpp"

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

  initial_builder* builder = new
    initial_builder();
  //initial_builder_cycle_conjecture();
  //initial_builder_stree_conjecture();
  state_manager<igraph_t>* manager = new basic_state_manager();
  dfs_finder<igraph_t>* finder = new dfs_finder<igraph_t>
    (config, builder, manager);

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
  delete manager;
  delete builder;
  delete config;

  return 0;
}

