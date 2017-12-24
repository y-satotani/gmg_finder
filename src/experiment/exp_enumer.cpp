
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
    cout << "output: n,d,Q,R,sspl_lb,test,ngraph,edge,state,time" << endl;
    return 1;
  }

  unsigned int n = (unsigned int) atoi(argv[1]);
  unsigned int d = (unsigned int) atoi(argv[2]);

  int test;
  unsigned long long extracted_states;
  double time;

  graph_config* config = new graph_config(n, d);
  graph_initr* builder = new stree_graph_initr(config);
  state_initr* manager = new matrix_opt_state_initr();
  vector<igraph_t> graphs = run_fbs_enumer
    (&test, &extracted_states, &time, builder, manager);

  cout << n << "," << d << ","
       << config->Q() << "," << config->R() << ","
       << config->sspl_lb() << "," << test << ","
       << graphs.size() << ","
       << builder->possible_edges().size() << ","
       << extracted_states << "," << time << endl;

  for(std::size_t gi = 0; gi < graphs.size(); gi++) {
    string filename;
    filename.append("n");  filename.append(to_string(n));
    filename.append("-d"); filename.append(to_string(d));
    filename.append("-g"); filename.append(to_string(gi+1));
    filename.append("-enumer.elist");
    ofstream fp;
    fp.open(filename, ios::out);
    for(int eid = 0; eid < igraph_ecount(&graphs[gi]); eid++) {
      igraph_integer_t v, w;
      igraph_edge(&graphs[gi], eid, &v, &w);
      fp << v+1 << " " << w+1;
      fp << endl;
    }
    fp.close();
    igraph_destroy(&graphs[gi]);
  }

  delete manager;
  delete builder;
  delete config;

  return 0;
}

