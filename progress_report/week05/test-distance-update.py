#!/usr/bin/env python
from __future__ import print_function, division
from random import choice
from itertools import combinations
import numpy as np
import networkx as nx

def update_distance_on_insert(D, S, e):
    Dnew, Snew = np.copy(D), np.copy(S)
    for s, t in combinations(range(D.shape[0]), 2):
        a, b = e
        if D[s, a] < 0 and D[s, b] < 0:
            continue # no change (not connected)
        elif D[s, a] < 0 and D[s, b] >= 0:
            a, b = b, a
        elif D[s, a] >= 0 and D[s, b] < 0:
            a, b = a, b
        elif D[s, a] > D[s, b]:
            a, b = b, a

        SHORTER, SAME, LONGER = -1, 0, 1
        dist_comp = SAME
        if not (D[s, a] < 0 or D[b, t] < 0) and D[s, t] < 0:
            dist_comp = SHORTER
        elif (D[s, a] < 0 or D[b, t] < 0) and not D[s, t] < 0:
            dist_comp = LONGER
        elif D[s, a] + D[b, t] + 1 < D[s, t]:
            dist_comp = SHORTER
        elif D[s, a] + D[b, t] + 1 > D[s, t]:
            dist_comp = LONGER

        near_a = D[s, a] >= 0 and D[s, b] < 0 or\
                 D[s, a] < D[s, b]

        if near_a and dist_comp is SHORTER:
            # (1)
            Dnew[s, t] = Dnew[t, s] = D[s, a] + D[b, t] + 1
            Snew[s, t] = Snew[t, s] = S[s, a] * S[b, t]

        elif near_a and dist_comp is SAME:
            # (2)
            #Dnew[s, t] = Dnew[t, s] = D[s, t]
            Snew[s, t] = Snew[t, s] = S[t, s] + S[s, a] * S[b, t]

        elif not near_a or dist_comp is LONGER:
            # (3)
            #Dnew[s, t] = Dnew[t, s] = D[s, t]
            #Snew[s, t] = Snew[t, s] = S[s, t]
            pass

    return Dnew, Snew

def update_distance_on_delete(D, S, e):
    Dnew, Snew = np.copy(D), np.copy(S)
    update_pair = []
    for s, t in combinations(range(D.shape[0]), 2):
        a, b = e
        if D[s, a] < 0 and D[s, b] < 0:
            continue # no change (not connected)
        elif D[s, a] < 0 and D[s, b] >= 0:
            a, b = b, a
        elif D[s, a] >= 0 and D[s, b] < 0:
            a, b = a, b
        elif D[s, a] > D[s, b]:
            a, b = b, a

        if D[s, a] + D[b, t] + 1 > D[s, t]:
            continue
        else: # D[s, a] + D[b, t] + 1 == D[s, t]
            Snew[s, t] = Snew[t, s] = S[s, t] - S[s, a] * S[b, t]
            if Snew[s, t] == 0:
                # set default value for no st-path
                Dnew[s, t] = Dnew[t, s] = -1
                update_pair.append((s, t))

    def no_ab_path_num(s, t):
        # determine st shortest path must go through ab
        a, b = e
        if D[s, a] < 0 and D[s, b] < 0:
            return 0
        elif D[s, a] < 0 and D[s, b] >= 0:
            a, b = b, a
        elif D[s, a] >= 0 and D[s, b] < 0:
            a, b = a, b
        elif D[s, a] > D[s, b]:
            a, b = b, a

        if D[s, a] + D[b, t] + 1 > D[s, t]:
            return S[s, t]
        else: # D[s, a] + D[b, t] + 1 == D[s, t]
            return S[s, t] - S[s, a] * S[b, t]

    for s, t in update_pair:
        min_dist = -1
        for v in range(D.shape[0]):
            if no_ab_path_num(s, v) == 0 or\
               no_ab_path_num(v, t) == 0:
                continue # have to go alpha-beta

            dist = D[s, v] + D[v, t]
            if min_dist < 0 or dist < min_dist:
                min_dist = dist
        Dnew[t, s] = Dnew[s, t] = min_dist

    # sort to calculate S in right order
    update_pair = sorted(
        filter(
            lambda t: Dnew[t[0], t[1]] > 1,
            update_pair
            ),
        key=lambda t: Dnew[t[0], t[1]]
        )
    #update_pair.sort(key=lambda t: Dnew[t[0], t[1]])

    for s, t in update_pair:
        sigma = 0
        for v in range(D.shape[0]):
            dist = Dnew[s, v] + Dnew[v, t]
            if dist == Dnew[s, t]:
                sigma += Snew[s, v] * Snew[v, t]
        # divide by (d_st - 1). every v on shortest path
        # shows (d_st - 1) times
        Snew[s, t] = Snew[t, s] = sigma // (Dnew[s, t] - 1)

    return Dnew, Snew

def update_distance(D, S, e, mode):
    if mode == 'i':
        return update_distance_on_insert(D, S, e)
    elif mode == 'd':
        return update_distance_on_delete(D, S, e)
    else:
        raise RuntimeError("unknown mode '{}'".format(mode))

def make_distance_table(G):
    N = len(G)
    S = np.empty((N, N), dtype=int)
    D = np.empty((N, N), dtype=int)
    for u, v in combinations(G.nodes(), 2):
        if not nx.has_path(G, u, v):
            S[u, v] = S[v, u] = 0
            D[u, v] = D[v, u] = -1
        else:
            p = list(nx.all_shortest_paths(G, u, v))
            S[u, v] = S[v, u] = len(p)
            D[u, v] = D[v, u] = len(p[0]) - 1
    for v in G.nodes():
        S[v, v] = 1
        D[v, v] = 0
    return D, S

def main():
    import random
    import matplotlib.pyplot as plt
    G = nx.random_regular_graph(2, 70)
    #G = nx.empty_graph(20)
    D, S = make_distance_table(G)

    while nx.number_of_edges(G) <\
          nx.number_of_nodes(G) * (nx.number_of_nodes(G) - 1) // 2:
        e = choice(nx.complement(G).edges())
        G.add_edge(*e)
        Dtrain, Strain = make_distance_table(G)
        D, S = update_distance(D, S, e, 'i')
        assert(np.array_equal(D, Dtrain))
        assert(np.array_equal(S, Strain))
    while nx.number_of_edges(G) > 0:
        e = choice(G.edges())
        G.remove_edge(*e)
        Dtrain, Strain = make_distance_table(G)
        D, S = update_distance(D, S, e, 'd')
        assert(np.array_equal(D, Dtrain))
        assert(np.array_equal(S, Strain))

if __name__ == '__main__':
    main()

