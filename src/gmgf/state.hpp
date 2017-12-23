
#ifndef _GMGF_STATE_HPP_
#define _GMGF_STATE_HPP_

#include "graph_config.hpp"

namespace gmgf {

  /**
   * \brief 各種探索における状態．
   */
  class state {
  protected:
    /**
     * \brief 探索対象のグラフの設定
     */
    graph_config* m_config;

  public:
    /**
     * \brief コンストラクタ．
     * \param config 探索対象のグラフの設定
     */
    state(graph_config* config);

    /**
     * \brief デストラクタ
     *
     * このとき，初期化時に与えられたグラフの設定は破棄されない．
     */
    virtual ~state() {};

    /**
     * \brief 状態に辺を追加できるか判定する．
     * \param e 辺
     * \param enter フロンティアに入る頂点リスト
     * \param exit フロンティアから出る頂点リスト
     * \return 追加できるなら真，できないなら偽
     */
    bool can_add_edge(edge_t e,
                      std::vector<vertex_t> enter,
                      std::vector<vertex_t> exit
                      );

    /**
     * \brief 状態に辺を追加しなくてよいか判定する．
     * \param e 辺
     * \param enter フロンティアに入る頂点リスト
     * \param exit フロンティアから出る頂点リスト
     * \return 追加しなくてよいなら真，そうでなければ偽
     */
    bool can_noadd_edge(edge_t e,
                        std::vector<vertex_t> enter,
                        std::vector<vertex_t> exit
                        );

    /**
     * \brief 状態が最終状態か判定する．
     * \return 最終状態なら真，そうでないなら偽
     */
    bool is_final();

    /**
     * \brief 次数の制約から，状態に辺を追加できるか判定する．
     * \param e 辺
     * \param enter フロンティアに入る頂点リスト
     * \param exit フロンティアから出る頂点リスト
     * \return 次数の制約から追加できるなら真，できないなら偽
     */
    virtual bool can_add_edge_degree(edge_t e,
                                     std::vector<vertex_t> enter,
                                     std::vector<vertex_t> exit
                                     ) = 0;

    /**
     * \brief 次数の制約から，状態に辺を追加しなくてよいか判定する．
     * \param e 辺
     * \param enter フロンティアに入る頂点リスト
     * \param exit フロンティアから出る頂点リスト
     * \return 次数の制約から追加しなくてよいなら真，そうでなければ偽
     */
    virtual bool can_noadd_edge_degree(edge_t e,
                                       std::vector<vertex_t> enter,
                                       std::vector<vertex_t> exit
                                       ) = 0;

    /**
     * \brief 閉路長の制約から，状態に辺を追加できるか判定する．
     * \param e 辺
     * \param enter フロンティアに入る頂点リスト
     * \param exit フロンティアから出る頂点リスト
     * \return 閉路長の制約から追加できるなら真，できないなら偽
     */
    virtual bool can_add_edge_cycle(edge_t e,
                                    std::vector<vertex_t> enter,
                                    std::vector<vertex_t> exit
                                    ) = 0;

    /**
     * \brief 閉路長の制約から，状態に辺を追加しなくてよいか判定する．
     * \param e 辺
     * \param enter フロンティアに入る頂点リスト
     * \param exit フロンティアから出る頂点リスト
     * \return 閉路長の制約から追加しなくてよいなら真，そうでなければ偽
     */
    virtual bool can_noadd_edge_cycle(edge_t e,
                                      std::vector<vertex_t> enter,
                                      std::vector<vertex_t> exit
                                      ) = 0;

    /**
     * \brief 直径の制約から，状態に辺を追加できるか判定する．
     * \param e 辺
     * \param enter フロンティアに入る頂点リスト
     * \param exit フロンティアから出る頂点リスト
     * \return 直径の制約から追加できるなら真，できないなら偽
     */
    virtual bool can_add_edge_diameter(edge_t e,
                                       std::vector<vertex_t> enter,
                                       std::vector<vertex_t> exit
                                       ) = 0;

    /**
     * \brief 直径の制約から，状態に辺を追加しなくてよいか判定する．
     * \param e 辺
     * \param enter フロンティアに入る頂点リスト
     * \param exit フロンティアから出る頂点リスト
     * \return 直径の制約から追加しなくてよいなら真，そうでなければ偽
     */
    virtual bool can_noadd_edge_diameter(edge_t e,
                                         std::vector<vertex_t> enter,
                                         std::vector<vertex_t> exit
                                         ) = 0;

    /**
     * \brief 次数の制約から，状態が最終状態か判定する．
     * \return 次数の制約から最終状態なら真，そうでないなら偽
     */
    virtual bool is_final_degree() = 0;

    /**
     * \brief 閉路長の制約から，状態が最終状態か判定する．
     * \return 閉路長の制約から最終状態なら真，そうでないなら偽
     */
    virtual bool is_final_cycle() = 0;

    /**
     * \brief 直径の制約から，状態が最終状態か判定する．
     * \return 直径の制約から最終状態なら真，そうでないなら偽
     */
    virtual bool is_final_diameter() = 0;

    /**
     * \brief 状態に辺を追加する．
     * \param e 辺
     */
    virtual void add_edge(edge_t e) = 0;

    /**
     * \brief 状態に辺を追加しない
     *
     * 基本的には何もしないが，状態が最大グラフを持つ場合は
     * 最大グラフから辺を削除する．
     * \param e 辺
     */
    virtual void noadd_edge(edge_t e) = 0;

    /**
     * \brief 状態を複製する．
     * \return 状態の複製
     */
    virtual state* copy() = 0;

    /**
     * \brief 状態が保持しているグラフを構築する．
     * \return グラフ
     * 使用後は，igraph_destroy関数で破棄しなければならない．
     */
    virtual igraph_t make_graph() = 0;

    /**
     * /brief 二つの状態が表すグラフの同型テストを行う．
     * /return 同型であればtrue,そうでなければfalse
     */
    virtual bool is_isomorphic(state* state) = 0;
  };

}

#endif // _GMGF_STATE_HPP_
