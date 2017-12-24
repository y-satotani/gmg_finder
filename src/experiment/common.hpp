
extern "C" {
#include <igraph.h>
}
#include "gmgf.hpp"
#include <ctime>
#include <vector>

unsigned int sspl(igraph_t* G) {
  igraph_matrix_t path;
  unsigned int sspl;
  igraph_matrix_init(&path,
                     igraph_vcount(G), igraph_vcount(G));
  igraph_shortest_paths(G, &path,
                        igraph_vss_all(), igraph_vss_all(),
                        IGRAPH_ALL);
  sspl = (unsigned int) igraph_matrix_sum(&path);
  igraph_matrix_destroy(&path);
  return sspl;
}

igraph_t run_dfs_finder(int* sspl_ret,
                        unsigned long long* n_node,
                        double* time,
                        gmgf::graph_initr* ginitr,
                        gmgf::state_initr* sinitr)
{
  gmgf::dfs_finder* finder = new gmgf::dfs_finder(ginitr, sinitr);

  clock_t begin = clock();
  igraph_t G = finder->next();
  clock_t end = clock();

  *sspl_ret = sspl(&G);
  *n_node   = finder->extracted_states();
  *time     = double(end - begin) / CLOCKS_PER_SEC;

  delete finder;
  return G;
}

std::vector<igraph_t> run_fbs_enumer(igraph_bool_t* test,
                                     unsigned long long* n_state,
                                     double* time,
                                     gmgf::graph_initr* ginitr,
                                     gmgf::state_initr* sinitr)
{
  gmgf::fbs_enumer* enumer = new gmgf::fbs_enumer(ginitr, sinitr);

  clock_t begin = clock();
  std::vector<igraph_t> Glist = enumer->enumerate();
  clock_t end = clock();

  *test = true;
  for(std::size_t gi = 0; gi < Glist.size(); gi++) {
    if(sspl(&Glist[gi]) != ginitr->get_config()->sspl_lb()) {
      *test = false;
    }
  }
  *n_state = enumer->extracted_states();
  *time    = double(end - begin) / CLOCKS_PER_SEC;

  delete enumer;
  return Glist;
}

void run_dfs_finder_full(int* n_graph,
                         int* sspl_min,
                         int* sspl_max,
                         unsigned long long* n_node,
                         double* time,
                         gmgf::graph_initr* ginitr,
                         gmgf::state_initr* sinitr)
{

  gmgf::dfs_finder* finder = new gmgf::dfs_finder(ginitr, sinitr);
  unsigned int N = ginitr->get_config()->n();

  *n_graph = 0;
  *sspl_min = N*N*N;
  *sspl_max = 0;
  clock_t clock_sum = 0;
  while(true) {
    clock_t begin = clock();
    igraph_t G = finder->next();
    clock_t end = clock();
    clock_sum += end - begin;

    if(igraph_vcount(&G) == 0) {
      igraph_destroy(&G);
      break;
    }

    (*n_graph)++;
    int s = sspl(&G);
    if(s > *sspl_max) *sspl_max = s;
    if(s < *sspl_min) *sspl_min = s;
    igraph_destroy(&G);
  }

  if(*n_graph == 0) *sspl_min = 0;
  *n_node = finder->extracted_states();
  *time = double(clock_sum) / CLOCKS_PER_SEC;
  delete finder;
}
