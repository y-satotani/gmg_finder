
#include "graph_initr.hpp"

namespace gmgf {

  graph_initr::graph_initr(graph_config* config) {
    m_config = config;
  }

  graph_config* graph_initr::get_config() {
    return m_config;
  }

  std::vector<std::pair<std::size_t, std::size_t> >
  graph_initr::vertex_frontier() {
    std::vector<std::pair<std::size_t, std::size_t> > frontier;
    std::vector<edge_t> l_edges = possible_edges();
    for(size_t vi = 0; vi < m_config->n(); vi++) {
      std::pair<int, int> p(-1, -1);
      for(size_t ei = 0; ei < l_edges.size(); ei++) {
        if(l_edges[ei].first == vi || l_edges[ei].second == vi) {
          if(p.first < 0) p.first = ei;
          p.second = ei;
        }
      }
      frontier.push_back(p);
    }
    return frontier;
  }

  igraph_t graph_initr::build() {
    igraph_t graph;
    igraph_empty(&graph, m_config->n(), IGRAPH_UNDIRECTED);
    std::vector<edge_t> t_edges = initial_edges();
    for(std::size_t i = 0; i < t_edges.size(); i++)
      igraph_add_edge(&graph, t_edges[i].first, t_edges[i].second);
    return graph;
  }

}
