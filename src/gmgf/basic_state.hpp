
#ifndef _GMGF_BASIC_STATE_HPP_
#define _GMGF_BASIC_STATE_HPP_

extern "C" {
#include <igraph.h>
}
#include "state.hpp"

namespace gmgf {

  /**
   * \brief 探索中のグラフを一つ含む基本的な状態
   */
  class basic_state : public state {
  protected:
    /** \brief 状態を表すグラフ */
    igraph_t G;

  public:
    /**
     * \brief コンストラクタ
     *
     * 初期化時に渡したグラフは igraph_destroy 関数で
     破棄してはならず，このオブジェクトの破棄と同時に破棄される．
     * \param config 探索対象のグラフ設定
     * \param G 状態を表すグラフ
     */
    basic_state(graph_config* config, igraph_t G);

    /**
     * \brief コピーコンストラクタ
     *
     * オブジェクトのコピーを作成する．
     * gmgf::basic_state::basic_state (graph_config*, igraph_t)と違い，
     * 被コピーオブジェクトのグラフをディープコピーする．
     * \param s 被コピーオブジェクト
     */
    basic_state(const basic_state& s);

    /**
     * \brief デストラクタ
     *
     * このとき，初期化時に与えられたグラフを
     * igraph_destroy 関数で破棄する．
     * グラフの設定は破棄しない．
     */
    virtual ~basic_state();

    virtual bool can_add_edge_degree(edge_t e,
                                     std::vector<vertex_t> enter,
                                     std::vector<vertex_t> exit
                                     );

    virtual bool can_noadd_edge_degree(edge_t e,
                                       std::vector<vertex_t> enter,
                                       std::vector<vertex_t> exit
                                       );

    virtual bool can_add_edge_cycle(edge_t e,
                                    std::vector<vertex_t> enter,
                                    std::vector<vertex_t> exit
                                    );

    virtual bool can_noadd_edge_cycle(edge_t e,
                                      std::vector<vertex_t> enter,
                                      std::vector<vertex_t> exit
                                      );

    virtual bool can_add_edge_diameter(edge_t e,
                                       std::vector<vertex_t> enter,
                                       std::vector<vertex_t> exit
                                       );

    virtual bool can_noadd_edge_diameter(edge_t e,
                                         std::vector<vertex_t> enter,
                                         std::vector<vertex_t> exit
                                         );

    virtual bool is_final_degree();
    virtual bool is_final_cycle();
    virtual bool is_final_diameter();

    virtual void add_edge(edge_t e);
    virtual void noadd_edge(edge_t e);
    virtual state* copy();

    virtual igraph_t make_graph();

    virtual bool is_isomorphic(state* state);
  };

}

#endif // _GMGF_BASIC_STATE_HPP_
