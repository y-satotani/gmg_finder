
extern "C" {
#include <igraph.h>
}
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <cstring>

#include "gmgf/graph_config.hpp"
#include "gmgf/initial_builder.hpp"
#include "gmgf/initial_builder_stree_conjecture.hpp"
#include "gmgf/minmax_state_manager.hpp"
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
igraph_t run_finder(int* sspl_ret,
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

  igraph_t ret;
  igraph_copy(&ret, &graph);

  manager->destroy(t);
  delete finder;
  return ret;
}

int main(int argc, char* argv[]) {

  if(argc < 2) {
    cout << "usage : " << argv[0] << " n d" << endl;
    cout << "output: n,d,Q,R,sspl_lb,sspl,edge,node,time" << endl;
    return 1;
  }

  unsigned int n = (unsigned int) atoi(argv[1]);
  unsigned int d = (unsigned int) atoi(argv[2]);

  int sspl;
  unsigned long long extracted_nodes;
  double time;

  graph_config* config = new graph_config(n, d);
  initial_builder* builder = new initial_builder_stree_conjecture();
  state_manager<igraph_pair_t>* manager = new minmax_state_manager();
  igraph_t graph = run_finder<igraph_pair_t>
    (&sspl, &extracted_nodes, &time, config, builder, manager);

  cout << n << "," << d << ","
       << config->Q() << "," << config->R() << ","
       << config->sspl_lb() << "," << sspl << ","
       << builder->possible_edges(config).size() << ","
       << extracted_nodes << "," << time << endl;

  if(sspl > 0) {
    string filename;
    filename.append("n");
    filename.append(to_string(n));
    filename.append("-d");
    filename.append(to_string(d));
    filename.append("-miner.elist");
    ofstream fp;
    fp.open(filename, ios::out);
    for(int eid = 0; eid < igraph_ecount(&graph); eid++) {
      igraph_integer_t v, w;
      igraph_edge(&graph, eid, &v, &w);
      fp << v+1 << " " << w+1;
      if(eid < igraph_ecount(&graph)-1)
        fp << endl;
    }
    fp.close();
  }

  igraph_destroy(&graph);
  delete manager;
  delete builder;
  delete config;

  return 0;
}

