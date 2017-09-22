
#include "generator.hpp"

using namespace ccheck;

namespace ccheck {

  bool dfs_generator::
  degree_constraint(std::size_t ei, igraph_t* G, bool add) {
    std::vector<vertex_t> v_exit_frontier;
    for(std::size_t i = 0; i < m_vert_range.size(); i++)
      if(m_vert_range[i].second == (int)ei)
        v_exit_frontier.push_back(i);

    igraph_vector_t degree;
    igraph_vector_init(&degree, 0);
    igraph_degree(G, &degree, igraph_vss_all(),
                  IGRAPH_ALL, 1);

    bool satisfy = true;
    if(add) {
      igraph_integer_t u = (igraph_integer_t)m_edges[ei].first;
      igraph_integer_t v = (igraph_integer_t)m_edges[ei].second;
      // degree must not exceed d
      satisfy &= igraph_vector_e(&degree, u) < m_config->d() ||
        igraph_vector_e(&degree, v) < m_config->d();
    }
    // all of vertices exit from frontier, must have degree d
    // (except selected edge, must have d-1)
    for(std::size_t i = 0; i < v_exit_frontier.size(); i++) {
      igraph_integer_t v = (igraph_integer_t)v_exit_frontier[i];
      if(add) {
        satisfy &= igraph_vector_e(&degree, v) == m_config->d() - 1;
      } else {
        satisfy &= igraph_vector_e(&degree, v) == m_config->d();
      }
    }
    igraph_vector_destroy(&degree);

    return satisfy;
  }

  bool dfs_generator::
  cycle_constraint(std::size_t ei, igraph_t* G, bool add) {
    if(!add) return true;

    igraph_integer_t u = (igraph_integer_t)m_edges[ei].first;
    igraph_integer_t v = (igraph_integer_t)m_edges[ei].second;
    igraph_matrix_t path_length;
    igraph_matrix_init(&path_length, 1, 1);
    igraph_shortest_paths(G, &path_length,
                          igraph_vss_1(u), igraph_vss_1(v), IGRAPH_ALL);

    bool satisfy = igraph_matrix_e(&path_length, 0, 0) >= 2*m_config->Q();
    igraph_matrix_destroy(&path_length);
    return satisfy;
  }

  bool dfs_generator::
  degree_constraint(igraph_t* G) {
    igraph_vector_t degree;
    igraph_vector_init(&degree, 0);
    igraph_degree(G, &degree, igraph_vss_all(),
                  IGRAPH_ALL, 1);
    bool is_regular = true;
    for(long int i = 0; i < igraph_vector_size(&degree); i++)
      if(igraph_vector_e(&degree, i) != m_config->d())
        is_regular = false;
    igraph_vector_destroy(&degree);
    return is_regular;
  }

  bool dfs_generator::
  diameter_constraint(igraph_t* G) {
    igraph_integer_t diam;
    igraph_diameter(G, &diam, 0, 0, 0, 0, 1);
    if(m_config->R() > 0)
      return (unsigned int)diam == m_config->Q() + 1;
    else
      return (unsigned int)diam == m_config->Q();
  }

  dfs_generator::dfs_generator(graph_config* conf) {
    m_config = conf;
    m_edges = m_config->leaf_edges();
    m_vert_range.clear();
    for(size_t vi = 0; vi < m_config->n(); vi++) {
      std::pair<int, int> p(-1, -1);
      for(size_t ei = 0; ei < m_edges.size(); ei++) {
        if(m_edges[ei].first == vi || m_edges[ei].second == vi) {
          if(p.first < 0) p.first = ei;
          p.second = ei;
        }
      }
      m_vert_range.push_back(p);
    }
    reset();
  }

  dfs_generator::~dfs_generator() {
    for(std::size_t i = 0; i < m_stack.size(); i++)
      igraph_destroy(&m_stack[i].second);
  }

  void dfs_generator::reset() {
    for(std::size_t i = 0; i < m_stack.size(); i++)
      igraph_destroy(&m_stack[i].second);
    m_stack.clear();
    m_stack.push_back(dfs_node_t(0, m_config->build_tree()));
  }

  igraph_t dfs_generator::next() {
    while(m_stack.size() > 0) {
      dfs_node_t node = m_stack.back();
      std::size_t ei = node.first;
      igraph_integer_t u = (igraph_integer_t)m_edges[ei].first;
      igraph_integer_t v = (igraph_integer_t)m_edges[ei].second;
      igraph_t G = node.second;
      m_stack.pop_back();

      if(ei == m_edges.size()) {
        if(degree_constraint(&G) && diameter_constraint(&G)) {
          return G;
        } else {
          igraph_destroy(&G);
          continue;
        }
      }

      if(degree_constraint(ei, &G, false) &&
         cycle_constraint(ei, &G, false)) {
        igraph_t H;
        igraph_copy(&H, &G);
        m_stack.push_back(dfs_node_t(ei+1, H));
      }

      if(degree_constraint(ei, &G, true) &&
         cycle_constraint(ei, &G, true)) {
        igraph_t H;
        igraph_copy(&H, &G);
        igraph_add_edge(&H, u, v);
        m_stack.push_back(dfs_node_t(ei+1, H));
      }

      igraph_destroy(&G);
    }

    igraph_t dummy;
    igraph_empty(&dummy, 0, IGRAPH_UNDIRECTED);
    return dummy;
  }

}
