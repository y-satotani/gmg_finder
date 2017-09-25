
#include "graph_config_r2.hpp"
#include <cassert>

namespace ccheck {

  graph_config_r2::graph_config_r2(std::size_t n, std::size_t d)
    : graph_config(n, d) {
    assert(graph_config::d() == 3);
    assert(R() == 2);
  }

  std::vector<edge_t> graph_config_r2::tree_edges() {
    std::vector<edge_t> t_edges = graph_config::tree_edges();
    size_t u = n_vert_btree(Q()-1, d());
    size_t v = u + (n_vert_btree(Q(), d()) - n_vert_btree(Q()-1, d())) /
      d();
    size_t x = n() - 2;
    t_edges.push_back(edge_t(u, x));
    t_edges.push_back(edge_t(v, x));
    return t_edges;
  }

  std::vector<edge_t> graph_config_r2::leaf_edges() {
    std::vector<vertex_t> l_verts = leaf_vertices();
    size_t u = n_vert_btree(Q()-1, d());
    size_t v = u + (n_vert_btree(Q(), d()) - n_vert_btree(Q()-1, d())) /
      d();
    size_t x = n() - 2;

    std::vector<edge_t> l_edges;
    for(std::size_t i = 0; i < l_verts.size(); i++)
      for(std::size_t j = 0; j < l_verts.size(); j++)
        if(i < j && ((l_verts[i] != u && l_verts[i] != v) || l_verts[j] != x))
          l_edges.push_back(edge_t(l_verts[i], l_verts[j]));
    return l_edges;
  }

}
