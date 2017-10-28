
#ifndef _GMGF_DFS_GENERIC_FINDER_HPP_
#define _GMGF_DFS_GENERIC_FINDER_HPP_

extern "C" {
#include <igraph.h>
}
#include <utility>
#include <vector>
#include "common/graph_config.hpp"
#include "common/initial_builder.hpp"
#include "common/state_manager.hpp"

namespace gmgf {

  template <typename S> class generic_finder {
  protected:
    gmgf::graph_config* m_config;
    gmgf::initial_builder* m_builder;
    gmgf::state_manager<S>* m_manager;
    std::vector<std::pair<std::size_t, S> > m_stack;
    std::vector<edge_t> m_e_possible;
    std::vector<std::pair<std::size_t, std::size_t> > m_v_range;
    unsigned long long m_extracted_nodes;

  public:
    generic_finder(graph_config* config,
                   initial_builder* builder,
                   state_manager<S>* manager) {
      m_config = config;
      m_builder = builder;
      m_manager = manager;
      m_e_possible = m_builder->possible_edges(m_config);
      m_v_range = m_builder->vertex_frontier(m_config);
      reset();
    }

    virtual ~generic_finder() {
      for(std::size_t i = 0; i < m_stack.size(); i++)
        m_manager->destroy(m_stack[i].second);
    }

    unsigned long long extracted_nodes() {
      return m_extracted_nodes;
    }

    void reset() {
      for(std::size_t i = 0; i < m_stack.size(); i++)
        m_manager->destroy(m_stack[i].second);
      m_stack.clear();
      m_stack.push_back(std::pair<std::size_t, S>
                        (0, m_manager->initial(m_config, m_builder)));
      m_extracted_nodes = 0;
    }

    S next() {
      while(m_stack.size() > 0) {
        ++m_extracted_nodes;

        std::pair<std::size_t, S> node = m_stack.back();
        std::size_t ei = node.first;
        edge_t e = m_e_possible[ei];
        S s = node.second;
        m_stack.pop_back();

        if(ei == m_e_possible.size()) {
          if(m_manager->can_accept(m_config, s)) {
            return s;
          } else {
            m_manager->destroy(s);
            continue;
          }
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

        for(int add = 0; add <= 1; add++) {
          if(m_manager->can_update
             (m_config, s, e, (bool)add, enter, exit)) {
            S t = m_manager->next(s, e, (bool)add);
            m_stack.push_back(std::pair<std::size_t, S>(ei+1, t));
          }
        }

        m_manager->destroy(s);
      }
      return m_manager->failure();
    }

  };
}

#endif // _GMGF_DFS_GENERIC_FINDER_HPP_
