
extern "C" {
#include <igraph.h>
}
#include <iostream>
#include "gmgf/graph_config.hpp"

using namespace std;
using namespace gmgf;

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
  // lower bound of sspl by Cerf et.al.
  cout << gconf.sspl_lb() << endl << endl;

  return 0;
}
