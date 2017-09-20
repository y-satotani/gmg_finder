

#include "generator.hpp"
#include "common/graph_config.hpp"
extern "C" {
#include <igraph.h>
}
#include <iostream>
#include <vector>

using namespace std;
using namespace ccheck;

size_t sspl(igraph_t* G) {
  igraph_matrix_t path_length;
  igraph_matrix_init(&path_length,
                     igraph_vcount(G), igraph_vcount(G));
  igraph_shortest_paths(G, &path_length,
                        igraph_vss_all(), igraph_vss_all(),
                        IGRAPH_ALL);
  size_t result = (size_t)igraph_matrix_sum(&path_length);
  igraph_matrix_destroy(&path_length);
  return result;
}

int main(int argc, char* argv[]) {
  graph_config gconf = graph_config(14, 3);
  dfs_generator generator(gconf);
  igraph_t graph = generator.next();
  cout << "sspl of graph: " << sspl(&graph) << endl
       << "lower bound  : " << gconf.sspl_lb() << endl;
  igraph_destroy(&graph);
  return 0;
}
