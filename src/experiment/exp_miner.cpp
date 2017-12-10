
extern "C" {
#include <igraph.h>
}
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include "common.hpp"

using namespace std;
using namespace gmgf;

int main(int argc, char* argv[]) {

  if(argc < 2) {
    cout << "usage : " << argv[0] << " n d" << endl;
    cout << "output: n,d,Q,R,sspl_lb,alg,sspl,edge,node,time" << endl;
    return 1;
  }

  unsigned int n = (unsigned int) atoi(argv[1]);
  unsigned int d = (unsigned int) atoi(argv[2]);

  int sspl;
  unsigned long long extracted_nodes;
  double time;

  graph_config* config = new graph_config(n, d);
  graph_initr* builder = new stree_graph_initr(config);
  state_initr* manager = new mmmtr_state_initr();
  igraph_t graph = run_dfs_finder
    (&sspl, &extracted_nodes, &time, builder, manager);

  cout << n << "," << d << ","
       << config->Q() << "," << config->R() << ","
       << config->sspl_lb() << ",matrix," << sspl << ","
       << builder->possible_edges().size() << ","
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

