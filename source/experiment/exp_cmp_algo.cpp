
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

char basic_bdr[] = "basic", cycle_bdr[] = "cycle", stree_bdr[] = "stree";
char basic_mgr[] = "basic", minmax_mgr[] = "minmax", mmmtr_mgr[] = "matrix";
char disable_srt[] = "basic", enable_srt[] = "sorted";

int main(int argc, char* argv[]) {
  if(argc < 6) {
    cout << "usage : " << argv[0]
         << " (basic|cycle|stree)"
         << " (basic|sorted)"
         << " (basic|minmax|matrix)"
         << " n d" << endl;
    cout << "output: n,d,Q,R,sspl_lb,bdr,str,mgr,"
         << "sspl,edge,node,time" << endl;
    return 1;
  }

  char* bdr_name = argv[1];
  char* srt_flag = argv[2];
  char* mgr_name = argv[3];
  unsigned int n = (unsigned int) atoi(argv[4]);
  unsigned int d = (unsigned int) atoi(argv[5]);

  graph_config* config = new graph_config(n, d);

  graph_initr* ginitr, * ginitr_base = NULL;
  if(strcmp(bdr_name, cycle_bdr) == 0)
    ginitr = new cycle_graph_initr(config);
  else if(strcmp(bdr_name, stree_bdr) == 0)
    ginitr = new stree_graph_initr(config);
  else
    ginitr = new basic_graph_initr(config);
  if(strcmp(srt_flag, enable_srt) == 0) {
    ginitr_base = ginitr;
    ginitr = new sorted_graph_initr(ginitr_base);
  }

  state_initr* sinitr;
  if(strcmp(mgr_name, minmax_mgr) == 0)
    sinitr = new minmax_state_initr();
  else if(strcmp(mgr_name, mmmtr_mgr) == 0)
    sinitr = new mmmtr_state_initr();
  else
    sinitr = new basic_state_initr();

  int sspl;
  unsigned long long extracted_nodes;
  double time;
  igraph_t G = run_dfs_finder(&sspl, &extracted_nodes, &time,
                              ginitr, sinitr);

  cout << n << "," << d << ","
       << config->Q() << "," << config->R() << ","
       << config->sspl_lb() << ","
       << bdr_name << "," << srt_flag << "," << mgr_name << ","
       << sspl << ","
       << ginitr->possible_edges().size() << ","
       << extracted_nodes << "," << time << endl;

  igraph_destroy(&G);
  delete sinitr;
  delete ginitr;
  if(ginitr_base) delete ginitr_base;
  delete config;

  return 0;
}

