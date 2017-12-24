
extern "C" {
#include <igraph.h>
}
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include "common.hpp"

using namespace std;
using namespace gmgf;

char basic_ginitr[] = "basic", cycle_ginitr[] = "cycle", stree_ginitr[] = "stree";
char basic_sinitr[] = "basic", minmax_sinitr[] = "minmax", mmmtr_sinitr[] ="matrix";
char disable_srt[] = "basic", enable_srt[] = "sorted";

int main(int argc, char* argv[]) {

  if(argc < 6) {
    cout << "usage : " << argv[0]
         << " (basic|cycle|stree)"
         << " (basic|sorted)"
         << " (basic|minmax|matrix)"
         << " n d" << endl;
    cout << "output: n,d,Q,R,sspl_lb,ginitr,sorted,sinitr,"
         << "test,n_graph,n_edge,n_state,time" << endl;
    return 1;
  }

  char* ginitr_name = argv[1];
  char* srt_flag = argv[2];
  char* sinitr_name = argv[3];
  unsigned int n = (unsigned int) atoi(argv[4]);
  unsigned int d = (unsigned int) atoi(argv[5]);

  graph_config* config = new graph_config(n, d);

  graph_initr* ginitr, * ginitr_base = NULL;
  if(strcmp(ginitr_name, cycle_ginitr) == 0)
    ginitr = new cycle_graph_initr(config);
  else if(strcmp(ginitr_name, stree_ginitr) == 0)
    ginitr = new stree_graph_initr(config);
  else
    ginitr = new basic_graph_initr(config);
  if(strcmp(srt_flag, enable_srt) == 0) {
    ginitr_base = ginitr;
    ginitr = new sorted_graph_initr(ginitr_base);
  }

  state_initr* sinitr;
  if(strcmp(sinitr_name, minmax_sinitr) == 0)
    sinitr = new minmax_state_initr();
  else if(strcmp(sinitr_name, mmmtr_sinitr) == 0)
    sinitr = new matrix_state_initr();
  else
    sinitr = new basic_state_initr();

  int test;
  unsigned long long extracted_states;
  double time;
  vector<igraph_t> graphs = run_fbs_enumer
    (&test, &extracted_states, &time, ginitr, sinitr);

  cout << n << "," << d << ","
       << config->Q() << "," << config->R() << ","
       << config->sspl_lb() << ","
       << ginitr_name << "," << srt_flag << "," << sinitr_name << ","
       << test << "," << graphs.size() << ","
       << ginitr->possible_edges().size() << ","
       << extracted_states << "," << time << endl;

  for(size_t gi = 0; gi < graphs.size(); gi++)
    igraph_destroy(&graphs[gi]);
  delete sinitr;
  delete ginitr;
  if(ginitr_base) delete ginitr_base;
  delete config;

  return 0;
}
