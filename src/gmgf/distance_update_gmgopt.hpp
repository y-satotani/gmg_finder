/** \file distance_update.hpp */

#ifndef _GMGF_DISTANCE_UPDATE_HPP_
#define _GMGF_DISTANCE_UPDATE_HPP_

extern "C" {
#include <igraph.h>
}

namespace gmgf {

  /**
   * \brief 辺の挿入に伴う頂点間距離の更新を行う．
   *
   * DnextとSnextは結果を格納するためのポインタである．
   * 呼び出しの前に igraph_matrix_init 関数で
   * 初期化されている必要がある．
   * \param Dnext 更新後の頂点間距離行列
   * \param D 更新前の頂点間距離行列
   * \param u 挿入する辺の端点
   * \param v 挿入する辺の端点
   */
  void update_distance_on_insert_gmgopt(igraph_matrix_t* Dnext,
                                        igraph_matrix_t* D,
                                        igraph_integer_t u,
                                        igraph_integer_t v);
  /**
   * \brief 辺の削除に伴う頂点間距離の更新を行う．
   *
   * DnextとSnextは結果を格納するためのポインタである．
   * 呼び出しの前に igraph_matrix_init 関数で
   * 初期化されている必要がある．
   * \param Dnext 更新後の頂点間距離行列
   * \param Snext 更新後の最短経路数行列
   * \param D 更新前の頂点間距離行列
   * \param S 更新前の最短経路数行列
   * \param u 削除する辺の端点
   * \param v 削除する辺の端点
   * \param diam 得られる直径
   */
  void update_distance_on_delete_gmgopt(igraph_matrix_t* Dnext,
                                        igraph_matrix_t* Snext,
                                        igraph_matrix_t* D,
                                        igraph_matrix_t* S,
                                        igraph_integer_t u,
                                        igraph_integer_t v,
                                        igraph_real_t* diam);

}

#endif // _GMGF_DISTANCE_UPDATE_HPP_
