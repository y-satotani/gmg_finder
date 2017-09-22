
#include "generator.hpp"
#include "common/graph_config_tconj.hpp"
extern "C" {
#include <argp.h>
#include <igraph.h>
}
#include <cstdlib>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;
using namespace ccheck;

struct arguments {
  unsigned int n;
  unsigned int d;
  string output_file;
  unsigned int max_graph;
};

static struct argp_option options[] = {
  {"max-graph",   'm', "NUM",      0, "number of graphs (default: unlimited)"},
  {"output-file", 'o', "OUT_FILE", 0, "output file (or prefix)"},
  {0},
};

static error_t parse_opt(int key, char* arg, struct argp_state *state) {
  struct arguments* arguments = (struct arguments*) state->input;
  unsigned int val;
  switch(key) {
  case 'm':
    arguments->max_graph = (unsigned int) atoi(arg);
    break;
  case 'o':
    arguments->output_file = (string) arg;
    break;
  case ARGP_KEY_ARG:
    val = (unsigned int) atoi(arg);
    if(val == 0)
      argp_error(state, "[nd] != 0");
    if(state->arg_num == 0)
      arguments->n = val;
    else if(state->arg_num == 1)
      arguments->d = val;
    if(arguments->n * arguments->d % 2 == 1)
      argp_error(state, "n*d is even (to make regular graph)");
    break;
  case ARGP_KEY_END:
    if(state->arg_num < 2)
      argp_error(state, "too few arguments");
    break;
  default:
    return ARGP_ERR_UNKNOWN;
  }
  return 0;
}

static char args_doc[] = "n d";

static struct argp argp = { options, parse_opt, args_doc, 0 };

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

void print_edge_list(ostream& s, igraph_t* G) {
  for(igraph_integer_t ei = 0; ei < igraph_ecount(G); ei++) {
    igraph_integer_t u, v;
    igraph_edge(G, ei, &u, &v);
    s << u << " " << v  << endl;
  }
}

int main(int argc, char* argv[]) {
  struct arguments args = { 0, 0, "", 1 };
  argp_parse(&argp, argc, argv, 0, 0, &args);

  graph_config* gconf = new graph_config_tconj(args.n, args.d);
  dfs_generator generator(gconf);
  igraph_t graph = generator.next();
  size_t count = 0;
  while(igraph_vcount(&graph) > 0 && count < args.max_graph) {
    if(args.output_file.length() > 0) {
      stringstream ss;
      ss << args.output_file << "-" << count;
      ofstream os(ss.str().c_str());
      print_edge_list(os, &graph);
      os.close();
    } else {
      if(count > 0) cout << endl;
      print_edge_list(cout, &graph);
    }

    igraph_destroy(&graph);
    graph = generator.next();
    count++;
  }
  igraph_destroy(&graph);

  return 0;
}
