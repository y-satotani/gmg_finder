
#include "generator.hpp"
#include "common/graph_config.hpp"
extern "C" {
#include <igraph.h>
}
#include <string>
#include <iostream>

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

const int k_cerf = 0;     // found and cerf
const int k_not_cerf = 1; // found but not cerf
const int k_no_graph = 2; // not found
const int k_na_graph = 3; // graph unavailable

int cerf_check(size_t n, size_t d) {
  if(d >= n || n*d % 2 == 1) return k_na_graph;

  graph_config* gconf = new graph_config(n, d);
  dfs_generator generator(gconf);
  igraph_t graph = generator.next();
  int status;

  if(igraph_vcount(&graph) == 0)
    status = k_no_graph;
  else if(sspl(&graph) != gconf->sspl_lb())
    status = k_not_cerf;
  else
    status = k_cerf;

  igraph_destroy(&graph);
  delete gconf;
  return status;
}

int main(int argc, char* argv[]) {
  size_t N = 12, D = 5;

  cout << "\\begin{table}" << endl;
  cout << "  \\centering" << endl;
  cout << "  \\begin{tabular}{|c|";
  for(size_t n = 4; n <= N; n++)
    cout << "c|";
  cout << "}" << endl;
  cout << "    \\hline" << endl;

  // header row
  cout << "   ";
  for(size_t n = 4; n <= N; n++)
    cout << " & " << n;
  cout << " \\\\ \\hline" << endl;

  for(size_t d = 3; d <= D; d++) {
    cout << "    " << d;
    for(size_t n = 4; n <= N; n++) {
      int status = cerf_check(n, d);
      string msg;
      switch(status) {
      case k_cerf:     msg = "\\checkmark"; break;
      case k_not_cerf: msg = "$\\times$"; break;
      case k_no_graph: msg = ""; break;
      case k_na_graph: msg = "NA"; break;
      }
      cout << " & " << msg;
      cerr << "pair: " << n << ", "
           << d << " finished" << endl;
    }
    cout << " \\\\ \\hline" << endl;
  }

  cout << "  \\end{tabular}" << endl;
  cout << "\\end{table}" << endl;

  return 0;
}
