
extern "C" {
#include <igraph.h>
}
#include <iostream>
#include "common/graph_config.hpp"
#include "common/initial_builder.hpp"
#include "common/initial_builder_stree_conjecture.hpp"
#include "common/initial_builder_cycle_conjecture.hpp"
#include "common/initial_builder_sorter.hpp"
#include "common/basic_state_manager.hpp"
#include "dfs/generic_finder.hpp"

using namespace std;
using namespace gmgf;

int main(int argc, char* argv[]) {

  graph_config* config = new graph_config(16, 3);
  initial_builder* bdr_origin = new initial_builder();
  initial_builder* bdr_stree_origin = new initial_builder_stree_conjecture();
  initial_builder* bdr_stree = new initial_builder_sorter(bdr_stree_origin);

  state_manager<igraph_t>* manager = new basic_state_manager();
  generic_finder<igraph_t>* fdr_origin = new generic_finder<igraph_t>
    (config, bdr_origin, manager);
  generic_finder<igraph_t>* fdr_stree_origin = new generic_finder<igraph_t>
    (config, bdr_stree_origin, manager);
  generic_finder<igraph_t>* fdr_stree = new generic_finder<igraph_t>
    (config, bdr_stree, manager);

  igraph_t graph;
  graph = fdr_origin->next();
  igraph_destroy(&graph);
  graph = fdr_stree_origin->next();
  igraph_destroy(&graph);
  graph = fdr_stree->next();
  igraph_destroy(&graph);

  cout << "basic        : " << fdr_origin->extracted_nodes() << endl
       << "stree unsort : " << fdr_stree_origin->extracted_nodes() << endl
       << "stree sorted : " << fdr_stree->extracted_nodes() << endl;

  delete fdr_origin;
  delete fdr_stree_origin;
  delete fdr_stree;
  delete bdr_origin;
  delete bdr_stree_origin;
  delete bdr_stree;
  delete manager;
  delete config;

  return 0;
}
