
#include "dfs_finder.hpp"

namespace gmgf {

  dfs_finder::dfs_finder(graph_initr* ginitr, state_initr* sinitr) {
    m_sinitr = sinitr;
    m_ginitr = ginitr;
    m_e_possible = m_ginitr->possible_edges();
    m_v_range = m_ginitr->vertex_frontier();
    reset();
  }

  dfs_finder::~dfs_finder() {
    for(std::size_t i = 0; i < m_stack.size(); i++)
      delete m_stack[i].second;
  }

  unsigned long long dfs_finder::extracted_nodes() {
    return m_extracted_states;
  }

  unsigned long long dfs_finder::extracted_states() {
    return m_extracted_states;
  }

  void dfs_finder::reset() {
    for(std::size_t i = 0; i < m_stack.size(); i++)
      delete m_stack[i].second;
    m_stack.clear();
    m_stack.push_back
      (std::pair<std::size_t, state*>(0, m_sinitr->initial(m_ginitr)));
    m_extracted_states = 0;
  }

  igraph_t dfs_finder::next() {
    while(m_stack.size() > 0) {
      ++m_extracted_states;

      std::pair<std::size_t, state*> node = m_stack.back();
      std::size_t ei = node.first;
      edge_t e = m_e_possible[ei];
      state* s = node.second;
      m_stack.pop_back();

      if(ei == m_e_possible.size()) {
        if(s->is_final()) {
          igraph_t G = s->make_graph();
          delete s;
          return G;
        }
        delete s;
        continue;
      }

      std::vector<vertex_t> enter;
      std::vector<vertex_t> exit;
      if(m_v_range[m_e_possible[ei].first].first == ei)
        enter.push_back(m_e_possible[ei].first);
      if(m_v_range[m_e_possible[ei].second].first == ei)
        enter.push_back(m_e_possible[ei].second);
      if(m_v_range[m_e_possible[ei].first].second == ei)
        exit.push_back(m_e_possible[ei].first);
      if(m_v_range[m_e_possible[ei].second].second == ei)
        exit.push_back(m_e_possible[ei].second);

      if(s->can_noadd_edge(e, enter, exit)) {
        state* t = s->copy();
        t->noadd_edge(e);
        m_stack.push_back(std::pair<std::size_t, state*>(ei+1, t));
      }
      if(s->can_add_edge(e, enter, exit)) {
        state* t = s->copy();
        t->add_edge(e);
        m_stack.push_back(std::pair<std::size_t, state*>(ei+1, t));
      }

      delete s;
    }

    igraph_t dummy;
    igraph_empty(&dummy, 0, 0);
    return dummy;
  }

}

