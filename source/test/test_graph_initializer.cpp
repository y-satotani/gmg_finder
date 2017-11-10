
extern "C" {
#include <igraph.h>
}
#include <iostream>
#include "gmgf/graph_config.hpp"
#include "gmgf/basic_graph_initr.hpp"

using namespace std;
using namespace gmgf;

int main(int argc, char* argv[]) {

  // testing specific graph configuration
  graph_config gconf(10, 3);
  basic_graph_initr initr(&gconf);
  // tree edges: edges in balanced tree
  vector<edge_t> t_edges = initr.initial_edges();
  for(size_t i = 0; i < t_edges.size(); i++) {
    cout << t_edges[i].first << " " << t_edges[i].second << endl;
  }
  cout << endl;

  // leaf edges: edges connecting two vertices (degree < d)
  vector<edge_t> l_edges = initr.possible_edges();
  for(size_t i = 0; i < l_edges.size(); i++) {
    cout << l_edges[i].first << " " << l_edges[i].second << endl;
  }
  cout << endl;

  // interface to igraph (example: calculates path length of 1->9 (3))
  igraph_t graph = initr.build();
  igraph_matrix_t path_length;
  igraph_matrix_init(&path_length, 1, 1);
  igraph_shortest_paths(&graph, &path_length,
                        igraph_vss_1(1),
                        igraph_vss_1(9),
                        IGRAPH_ALL);
  cout << igraph_matrix_e(&path_length, 0, 0) << endl;
  igraph_matrix_destroy(&path_length);
  igraph_destroy(&graph);

  return 0;
}
