
#include "initial_builder_sorter.hpp"
#include <algorithm>

namespace ccheck {

  initial_builder_sorter::initial_builder_sorter(initial_builder* builder) {
    m_builder = builder;
  }

  vertex_t initial_builder_sorter::parent_of(graph_config* c, vertex_t v) {
    return m_builder->parent_of(c, v);
  }

  std::vector<vertex_t>
  initial_builder_sorter::initial_vertices(graph_config* c) {
    return m_builder->initial_vertices(c);
  }

  std::vector<vertex_t>
  initial_builder_sorter::possible_vertices(graph_config* c) {
    return m_builder->possible_vertices(c);
  }

  std::vector<edge_t>
  initial_builder_sorter::initial_edges(graph_config* c) {
    return m_builder->initial_edges(c);
  }

  vertex_t _find_least_vertex
  (std::vector<vertex_t> vertices, std::vector<edge_t> edges) {
    vertex_t min_v = vertices[0];
    unsigned long cost, min_cost = edges.size();
    unsigned int vi, ei;
    vertex_t v;
    edge_t e;
    for(vi = 0; vi < vertices.size(); vi++) {
      v = vertices[vi];
      cost = 0;
      for(ei = 0; ei < edges.size(); ei++) {
        e = edges[ei];
        if(v == e.first || v == e.second) cost++;
      }
      if(cost < min_cost) {
        min_v = v;
        min_cost = cost;
      }
    }
    return min_v;
  }

  std::vector<edge_t>
  initial_builder_sorter::possible_edges(graph_config* c) {
    std::vector<vertex_t> orig_v = m_builder->possible_vertices(c);
    std::vector<edge_t> orig_e = m_builder->possible_edges(c);
    std::vector<edge_t> edges;
    while(orig_e.size() > 0) {
      vertex_t v = _find_least_vertex(orig_v, orig_e);
      orig_v.erase(std::remove
                   (orig_v.begin(), orig_v.end(), v),
                   orig_v.end());
      std::copy_if(orig_e.begin(), orig_e.end(), std::back_inserter(edges),
                   [v](edge_t e){return e.first == v || e.second == v;});
      orig_e.erase(std::remove_if
                   (orig_e.begin(), orig_e.end(),
                    [v](edge_t e){return e.first == v || e.second == v;}),
                   orig_e.end());
    }
    return edges;
  }

}
