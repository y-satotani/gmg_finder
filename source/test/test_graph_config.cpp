
#include <iostream>
#include "common/graph_config.hpp"

using namespace std;
using namespace ccheck;

int main(int argc, char* argv[]) {
  graph_config gconf(10, 3);
  std::cout << "initialized: n = " << gconf.n() << ", d = " << gconf.d() << std::endl;
  return 0;
}
