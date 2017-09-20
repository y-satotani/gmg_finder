

#include "generator.hpp"
#include "common/graph_config.hpp"
#include <iostream>
#include <vector>

using namespace std;
using namespace ccheck;

int main(int argc, char* argv[]) {
  cout << "Hello World" << endl;
  dfs_generator g(graph_config(10, 3));
  return 0;
}
