
extern "C" {
#include <igraph.h>
}
#include <iostream>
#include "common/graph_config.hpp"

using namespace std;
using namespace ccheck;

int main(int argc, char* argv[]) {
  graph_config gconf(22, 3);
  std::cout << "initialized: n = " << gconf.n() <<
    ", d = " << gconf.d() << std::endl;

  for(unsigned int vi = 0; vi <= gconf.n(); vi++)
    std::cout << gconf.depth(vi) << " ";
  std::cout << std::endl;

  igraph_t graph = gconf.build_base_graph();
  std::cout << igraph_vcount(&graph) << std::endl;
  igraph_destroy(&graph);
  return 0;
}
