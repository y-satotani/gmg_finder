
#include <iostream>
#include "gmgf/graph_config.hpp"

using namespace std;
using namespace gmgf;

int main(int argc, char* argv[]) {

  unsigned int D[] = {3, 4, 7, 8, 16};
  cout << "degree,order,aspl" << endl;
  // sspl_lb() function for each grpah configuration
  for(unsigned int di = 0; di < 5; di++) {
    unsigned int d = D[di];
    for(unsigned int n = d+1; n <= 1000; n++) {
      if(n * d % 2 == 1) continue;
      graph_config gconf(n, d);
      cout << d << "," << n << "," <<
        (double)gconf.sspl_lb() / (n*(n-1)) << endl;
    }
  }

  return 0;
}
