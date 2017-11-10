
extern "C" {
#include <igraph.h>
}
#include <iostream>
#include "gmgf/graph_config.hpp"
#include "gmgf/graph_initr.hpp"
#include "gmgf/cycle_graph_initr.hpp"
#include "gmgf/sorted_graph_initr.hpp"
#include "gmgf/basic_state_initr.hpp"
#include "gmgf/dfs_finder.hpp"

using namespace std;
using namespace gmgf;

int main(int argc, char* argv[]) {

  graph_config* config = new graph_config(16, 3);
  graph_initr* ginitr_cycle = new cycle_graph_initr(config);
  graph_initr* ginitr_sorted = new sorted_graph_initr(ginitr_cycle);
  basic_state_initr* sinitr = new basic_state_initr();
  dfs_finder* finder_cycle = new dfs_finder(ginitr_cycle, sinitr);
  dfs_finder* finder_sorted = new dfs_finder(ginitr_sorted, sinitr);

  igraph_t graph;
  graph = finder_cycle->next();
  igraph_destroy(&graph);
  graph = finder_sorted->next();
  igraph_destroy(&graph);

  cout << "cycle unsort : " << finder_cycle->extracted_nodes() << endl
       << "cycle sorted : " << finder_sorted->extracted_nodes() << endl;

  delete finder_cycle;
  delete finder_sorted;
  delete sinitr;
  delete ginitr_cycle;
  delete ginitr_sorted;
  delete config;

  return 0;
}
