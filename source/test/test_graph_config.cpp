
extern "C" {
#include <igraph.h>
}
#include <iostream>
#include "common/graph_config.hpp"

using namespace std;
using namespace ccheck;

int main(int argc, char* argv[]) {

  // Q() and R() function for each grpah configuration
  for(unsigned int n = 10; n < 30; n++)
    for(unsigned int d = 3; d < 7; d++) {
      if(n * d % 2 == 1) continue;
      graph_config gconf(n, d);
      cout << n << " " << d << " " <<
        gconf.Q() << " " << gconf.R() << endl;
    }
  cout << endl;

  // testing specific graph configuration
  graph_config gconf(10, 3);

  // tree edges: edges in balanced tree
  vector<edge_t> t_edges = gconf.tree_edges();
  for(size_t i = 0; i < t_edges.size(); i++) {
    cout << t_edges[i].first << " " << t_edges[i].second << endl;
  }
  cout << endl;

  // leaf edges: edges connecting two vertices (degree < d)
  vector<edge_t> l_edges = gconf.leaf_edges();
  for(size_t i = 0; i < l_edges.size(); i++) {
    cout << l_edges[i].first << " " << l_edges[i].second << endl;
  }
  cout << endl;

  // lower bound of sspl by Cerf et.al.
  cout << gconf.sspl_lb() << endl << endl;

  // interface to igraph (example: calculates path length of 1->9 (3))
  igraph_t graph = gconf.build_tree();
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
