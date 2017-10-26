
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
#include "common/initial_builder_sorter.hpp"

#include "common/basic_state_manager.hpp"
#include "common/minmax_state_manager.hpp"

#include "dfs/generic_finder.hpp"

using namespace std;
using namespace ccheck;

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

void run_sorted_finder(int* sspl_ret,
                       unsigned long long* n_node,
                       double* time,
                       graph_config* config,
                       initial_builder* builder)
{
  initial_builder* sorted_builder = new initial_builder_sorter(builder);
  state_manager<igraph_t>* manager = new basic_state_manager();
  generic_finder<igraph_t>* finder = new generic_finder<igraph_t>
    (config, sorted_builder, manager);

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
  delete sorted_builder;
}

char basic_bdr[] = "basic", cycle_bdr[] = "cycle", stree_bdr[] = "stree";
char disable_srt[] = "basic", enable_srt[] = "sorted";

int main(int argc, char* argv[]) {

  if(argc < 5) {
    cout << "usage : " << argv[0] << " (basic|cycle|stree)"
         << " (basic|sorted)" << " n d" << endl;
    cout << "output: n,d,Q,R,sspl_lb,bdr,srt,sspl,node,time" << endl;
    return 1;
  }

  char* bdr_name = argv[1];
  char* srt_name = argv[2];
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
  if(strcmp(srt_name, enable_srt) == 0)
    run_sorted_finder(&sspl, &extracted_nodes, &time, config, builder);
  else
    run_basic_finder(&sspl, &extracted_nodes, &time, config, builder);

  cout << n << "," << d << ","
       << config->Q() << "," << config->R() << ","
       << config->sspl_lb() << ","
       << bdr_name << "," << srt_name << ","
       << sspl << "," << extracted_nodes << "," << time << endl;

  delete builder;
  delete config;

  return 0;
}

