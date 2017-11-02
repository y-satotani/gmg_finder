
extern "C" {
#include <igraph.h>
}
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstring>

#include "gmgf/graph_config.hpp"
#include "gmgf/initial_builder.hpp"

#include "gmgf/minmax_state_manager.hpp"
#include "gmgf/mmmtr_state_manager.hpp"

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

template <typename T>
void run_finder(int* sspl_ret,
                unsigned long long* n_node,
                double* time,
                graph_config* config,
                initial_builder* builder,
                state_manager<T>* manager)
{

  dfs_finder<T>* finder = new dfs_finder<T>(config, builder, manager);

  clock_t begin = clock();
  T t = finder->next();
  clock_t end = clock();
  double cpu_time = double(end - begin) / CLOCKS_PER_SEC;
  igraph_t graph = manager->graph(t);

  *sspl_ret = sspl(&graph);
  *n_node   = finder->extracted_nodes();
  *time     = cpu_time;

  manager->destroy(t);
  delete finder;
}

char basic_mgr[] = "basic", minmax_mgr[] = "minmax", mmmtr_mgr[] = "matrix";

int main(int argc, char* argv[]) {

  if(argc < 3) {
    cout << "usage : " << argv[0] << " (basic|minmax|matrix) n d" << endl;
    cout << "output: n,d,Q,R,sspl_lb,bdr,mgr,srt,sspl,edge,node,time" << endl;
    return 1;
  }

  char* mgr_name = argv[1];
  unsigned int n = (unsigned int) atoi(argv[2]);
  unsigned int d = (unsigned int) atoi(argv[3]);

  graph_config* config = new graph_config(n, d);

  initial_builder* builder = new initial_builder();

  int sspl;
  unsigned long long extracted_nodes;
  double time;
  if(strcmp(mgr_name, minmax_mgr) == 0) {
    state_manager<igraph_pair_t>* manager = new minmax_state_manager();
    run_finder<igraph_pair_t>
      (&sspl, &extracted_nodes, &time, config, builder, manager);
    delete manager;
  } else if(strcmp(mgr_name, mmmtr_mgr) == 0) {
    state_manager<igraph_mmmtr_t>* manager = new mmmtr_state_manager();
    run_finder<igraph_mmmtr_t>
      (&sspl, &extracted_nodes, &time, config, builder, manager);
    delete manager;
  } else {
    state_manager<igraph_t>* manager = new basic_state_manager();
    run_finder<igraph_t>
      (&sspl, &extracted_nodes, &time, config, builder, manager);
    delete manager;
  }

  cout << n << "," << d << ","
       << config->Q() << "," << config->R() << ","
       << config->sspl_lb() << ","
       << mgr_name << ","
       << sspl << "," << builder->possible_edges(config).size() << ","
       << extracted_nodes << "," << time << endl;

  delete builder;
  delete config;

  return 0;
}

