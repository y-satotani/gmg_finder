#include "distance_update.hpp"
#include <iostream>

namespace gmgf {

  void _sort_two_vertices_by_distance(igraph_integer_t* near,
                                      igraph_integer_t* far,
                                      igraph_matrix_t* D,
                                      igraph_integer_t s,
                                      igraph_integer_t u,
                                      igraph_integer_t v) {
    if(igraph_matrix_e(D, s, u) == IGRAPH_INFINITY &&
       igraph_matrix_e(D, s, v) == IGRAPH_INFINITY) {
      *near = *far = -1;
    } else if(igraph_matrix_e(D, s, u) <= igraph_matrix_e(D, s, v)) {
      *near = u;
      *far = v;
    } else {
      *near = v;
      *far = u;
    }
  }

  void update_distance_on_insert(igraph_matrix_t* Dnext,
                                 igraph_matrix_t* Snext,
                                 igraph_matrix_t* D,
                                 igraph_matrix_t* S,
                                 igraph_integer_t u,
                                 igraph_integer_t v) {
    int s, t;
    igraph_integer_t a, b;
    igraph_real_t dsa, dsb, dbt, dst;
    igraph_real_t ssa, sbt, sst;
    for(s = 0; s < igraph_matrix_nrow(D); s++) {
      for(t = 0; t < igraph_matrix_nrow(D); t++) {
        if(s > t) continue;
        if(s == t) {
          igraph_matrix_set(Dnext, s, s, 0);
          igraph_matrix_set(Snext, s, s, 1);
          continue;
        }
        _sort_two_vertices_by_distance(&a, &b, D, s, u, v);
        dsa = igraph_matrix_e(D, s, a);
        dsb = igraph_matrix_e(D, s, b);
        dbt = igraph_matrix_e(D, b, t);
        dst = igraph_matrix_e(D, s, t);
        ssa = igraph_matrix_e(S, s, a);
        sbt = igraph_matrix_e(S, b, t);
        sst = igraph_matrix_e(S, s, t);

        if(dsa < dsb && dsa + dbt + 1 < dst) {
          dst = dsa + dbt + 1;
          sst = (igraph_integer_t)ssa * (igraph_integer_t)sbt;
        } else if(dsa < dsb && dsa + dbt + 1 == dst) {
          sst = (igraph_integer_t)sst +
            (igraph_integer_t)ssa * (igraph_integer_t)sbt;
        } else {
        }

        igraph_matrix_set(Dnext, s, t, dst);
        igraph_matrix_set(Dnext, t, s, dst);
        igraph_matrix_set(Snext, s, t, sst);
        igraph_matrix_set(Snext, t, s, sst);
      }
    }
  }

  igraph_integer_t _path_num_not_contain(igraph_matrix_t* D,
                                         igraph_matrix_t* S,
                                         igraph_integer_t s,
                                         igraph_integer_t t,
                                         igraph_integer_t u,
                                         igraph_integer_t v) {
    if(igraph_matrix_e(S, s, t) == 0) return 0; // no s-t path
    igraph_integer_t a, b;
    _sort_two_vertices_by_distance(&a, &b, D, s, u, v);
    if(a < 0) return igraph_matrix_e(S, s, t); // no path reduction
    if(igraph_matrix_e(D, s, t) <
       igraph_matrix_e(D, s, a) + igraph_matrix_e(D, b, t) + 1)
      return igraph_matrix_e(S, s, t);
    else
      return igraph_matrix_e(S, s, t) -
        igraph_matrix_e(S, s, a) * igraph_matrix_e(S, b, t);
  }

  void update_distance_on_delete(igraph_matrix_t* Dnext,
                                 igraph_matrix_t* Snext,
                                 igraph_matrix_t* D,
                                 igraph_matrix_t* S,
                                 igraph_integer_t u,
                                 igraph_integer_t v) {
    int i, s, t;
    igraph_integer_t w;
    igraph_vector_t update_pair_s;
    igraph_vector_t update_pair_t;
    igraph_vector_t update_dist;
    igraph_vector_init(&update_pair_s, 0);
    igraph_vector_init(&update_pair_t, 0);
    igraph_vector_init(&update_dist, 0);

    for(s = 0; s < igraph_matrix_nrow(D); s++) {
      for(t = 0; t < igraph_matrix_nrow(D); t++) {
        if(s > t) continue;
        if(s == t) {
          igraph_matrix_set(Dnext, s, s, 0);
          igraph_matrix_set(Snext, s, s, 1);
          continue;
        }
        igraph_integer_t npath = _path_num_not_contain(D, S, s, t, u, v);
        if(npath > 0 || igraph_matrix_e(S, s, t) == 0) {
          igraph_matrix_set(Dnext, s, t, igraph_matrix_e(D, s, t));
          igraph_matrix_set(Dnext, t, s, igraph_matrix_e(D, s, t));
          igraph_matrix_set(Snext, s, t, npath);
          igraph_matrix_set(Snext, t, s, npath);
          continue;
        }
        igraph_real_t mindist = IGRAPH_INFINITY;
        for(w = 0; w < igraph_matrix_nrow(D); w++) {
          if(_path_num_not_contain(D, S, s, w, u, v) == 0 ||
             _path_num_not_contain(D, S, w, t, u, v) == 0)
            continue;
          igraph_integer_t dist =
            igraph_matrix_e(D, s, w) + igraph_matrix_e(D, w, t);
          if(dist < mindist)
            mindist = dist;
        }

        if(mindist == IGRAPH_INFINITY) {
          igraph_matrix_set(Dnext, s, t, IGRAPH_INFINITY);
          igraph_matrix_set(Dnext, t, s, IGRAPH_INFINITY);
          igraph_matrix_set(Snext, s, t, 0);
          igraph_matrix_set(Snext, t, s, 0);
        } else {
          igraph_matrix_set(Dnext, s, t, (igraph_integer_t)mindist);
          igraph_matrix_set(Dnext, t, s, (igraph_integer_t)mindist);
          // add to update list to appropriate place
          long int pos;
          igraph_vector_binsearch(&update_dist, mindist, &pos);
          igraph_vector_insert(&update_dist, pos, mindist);
          igraph_vector_insert(&update_pair_s, pos, s);
          igraph_vector_insert(&update_pair_t, pos, t);
        }
      }
    }

    for(i = 0; i < igraph_vector_size(&update_dist); i++) {
      s = (int)igraph_vector_e(&update_pair_s, i);
      t = (int)igraph_vector_e(&update_pair_t, i);
      igraph_integer_t dist = (igraph_integer_t)
        igraph_vector_e(&update_dist, i);
      igraph_integer_t sigma = 0;
      for(w = 0; w < igraph_matrix_nrow(D); w++) {
        igraph_integer_t dsw = (igraph_integer_t)igraph_matrix_e(Dnext, s, w);
        igraph_integer_t dwt = (igraph_integer_t)igraph_matrix_e(Dnext, w, t);
        if(w != s && w != t && dist == dsw + dwt)
          sigma += (igraph_integer_t)igraph_matrix_e(Snext, s, w) *
            (igraph_integer_t)igraph_matrix_e(Snext, w, t);
      }
      sigma /= (dist - 1);
      igraph_matrix_set(Snext, s, t, sigma);
      igraph_matrix_set(Snext, t, s, sigma);
    }

    igraph_vector_destroy(&update_pair_s);
    igraph_vector_destroy(&update_pair_t);
    igraph_vector_destroy(&update_dist);
  }

  void set_distance_matrix_with_path_num(igraph_matrix_t* D,
                                         igraph_matrix_t* S,
                                         igraph_t* G) {

    igraph_vector_t nrgeo;
    igraph_vector_ptr_t paths;
    int row, col, i, tail;

    for(row = 0; row < igraph_vcount(G); row++) {
      igraph_vector_ptr_init(&paths, 0);
      igraph_vector_init(&nrgeo, 0);

      igraph_get_all_shortest_paths(G, &paths, &nrgeo,
                                    row, igraph_vss_all(),
                                    IGRAPH_ALL);

      col = tail = 0;
      while(col < igraph_vcount(G)) {
        igraph_vector_t* path = (igraph_vector_t*)
          igraph_vector_ptr_e(&paths, tail);
        if(igraph_vector_e(&nrgeo, col) > 0)
          igraph_matrix_set(D, row, col, igraph_vector_size(path)-1);
        else
          igraph_matrix_set(D, row, col, IGRAPH_INFINITY);
        igraph_matrix_set(S, row, col, igraph_vector_e(&nrgeo, col));
        tail += igraph_vector_e(&nrgeo, col);
        col++;
      }

      for(i = 0; i < igraph_vector_ptr_size(&paths); i++) {
        igraph_vector_destroy((igraph_vector_t*)
                              igraph_vector_ptr_e(&paths, i));
        free(igraph_vector_ptr_e(&paths, i));
        igraph_vector_ptr_set(&paths, i, 0);
      }
      igraph_vector_ptr_destroy(&paths);
      igraph_vector_destroy(&nrgeo);
    }
  }

}
