
#include "fbs_enumer.hpp"
#include <iostream>

namespace gmgf {

  fbs_enumer::fbs_enumer(graph_initr* ginitr, state_initr* sinitr) {
    m_sinitr = sinitr;
    m_ginitr = ginitr;
    m_e_possible = m_ginitr->possible_edges();
    m_v_range = m_ginitr->vertex_frontier();
    m_extracted_states = 0;
  }

  unsigned long long fbs_enumer::extracted_states() {
    return m_extracted_states;
  }

  std::vector<igraph_t> fbs_enumer::enumerate() {
    std::vector<state*> prev_states, next_states;

    prev_states.push_back(m_sinitr->initial(m_ginitr));
    for(std::size_t ei = 0; ei < m_e_possible.size(); ei++) {
      edge_t e = m_e_possible[ei];
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

      for(std::size_t si = 0; si < prev_states.size(); si++) {
        ++m_extracted_states;
        state* s = prev_states[si];
        if(s->can_add_edge(e, enter, exit)) {
          state* t = s->copy();
          t->add_edge(e);
          bool is_new = true;
          for(std::size_t ui = 0; ui < next_states.size(); ui++)
            if(t->is_isomorphic(next_states[ui])) {
              is_new = false; break;
            }
          if(is_new) next_states.push_back(t);
          else delete t;
        }
        if(s->can_noadd_edge(e, enter, exit)) {
          state* t = s->copy();
          t->noadd_edge(e);
          bool is_new = true;
          for(std::size_t ui = 0; ui < next_states.size(); ui++)
            if(t->is_isomorphic(next_states[ui])) {
              is_new = false; break;
            }
          if(is_new) next_states.push_back(t);
          else delete t;
        }
        delete s;
      }
      prev_states = next_states;
      next_states.clear();
    }

    std::vector<igraph_t> graphs;
    for(std::size_t si = 0; si < prev_states.size(); si++) {
      ++m_extracted_states;
      state* s = prev_states[si];
      if(s->is_final()) graphs.push_back(s->make_graph());
      delete s;
    }
    return graphs;
  }
}
