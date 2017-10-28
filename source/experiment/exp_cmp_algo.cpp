
extern "C" {
#include <igraph.h>
}
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstring>

#include "common/graph_config.hpp"
#include "common/initial_builder.hpp"
#include "common/initial_builder_cycle_conjecture.hpp"
#include "common/initial_builder_stree_conjecture.hpp"

#include "common/basic_state_manager.hpp"
#include "common/minmax_state_manager.hpp"

#include "dfs/generic_finder.hpp"

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

void run_basic_finder(int* sspl_ret,
                      unsigned long long* n_node,
                      double* time,
                      graph_config* config,
                      initial_builder* builder)
{
  state_manager<igraph_t>* manager = new basic_state_manager();
  generic_finder<igraph_t>* finder = new generic_finder<igraph_t>
    (config, builder, manager);

  clock_t begin = clock();
  igraph_t graph = finder->next();
  clock_t end = clock();
  double cpu_time = double(end - begin) / CLOCKS_PER_SEC;

  *sspl_ret = sspl(&graph);
  *n_node   = finder->extracted_nodes();
  *time     = cpu_time;

  igraph_destroy(&graph);
  delete finder;
  delete manager;
}

void run_minmax_finder(int* sspl_ret,
                       unsigned long long* n_node,
                       double* time,
                       graph_config* config,
                       initial_builder* builder)
{
  state_manager<igraph_pair_t>* manager = new minmax_state_manager();
  generic_finder<igraph_pair_t>* finder = new generic_finder<igraph_pair_t>
    (config, builder, manager);

  clock_t begin = clock();
  igraph_pair_t t = finder->next();
  clock_t end = clock();
  double cpu_time = double(end - begin) / CLOCKS_PER_SEC;
  igraph_t graph = t.first;

  *sspl_ret = sspl(&graph);
  *n_node   = finder->extracted_nodes();
  *time     = cpu_time;

  igraph_destroy(&t.first);
  igraph_destroy(&t.second);
  delete finder;
  delete manager;
}

char basic_bdr[] = "basic", cycle_bdr[] = "cycle", stree_bdr[] = "stree";
char basic_mgr[] = "basic", minmax_mgr[] = "minmax";

int main(int argc, char* argv[]) {

  if(argc < 5) {
    cout << "usage : " << argv[0] << " (basic|cycle|stree)"
         << " (basic|minmax)" << " n d" << endl;
    cout << "output: n,d,Q,R,sspl_lb,bdr,mgr,sspl,node,time" << endl;
    return 1;
  }

  char* bdr_name = argv[1];
  char* mgr_name = argv[2];
  unsigned int n = (unsigned int) atoi(argv[3]);
  unsigned int d = (unsigned int) atoi(argv[4]);

  graph_config* config = new graph_config(n, d);

  initial_builder* builder;
  if(strcmp(bdr_name, cycle_bdr) == 0)
    builder = new initial_builder_cycle_conjecture();
  else if(strcmp(bdr_name, stree_bdr) == 0)
    builder = new initial_builder_stree_conjecture();
  else
    builder = new initial_builder();

  int sspl;
  unsigned long long extracted_nodes;
  double time;
  if(strcmp(mgr_name, minmax_mgr) == 0)
    run_minmax_finder(&sspl, &extracted_nodes, &time, config, builder);
  else
    run_basic_finder(&sspl, &extracted_nodes, &time, config, builder);

  cout << n << "," << d << ","
       << config->Q() << "," << config->R() << ","
       << config->sspl_lb() << ","
       << bdr_name << "," << mgr_name << ","
       << sspl << "," << extracted_nodes << "," << time << endl;

  delete builder;
  delete config;

  return 0;
}

