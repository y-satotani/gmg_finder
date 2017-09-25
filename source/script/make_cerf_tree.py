#!/usr/bin/env python
from __future__ import print_function
import sys
from itertools import izip, product
import networkx as nx
from build_base_graph import *

k = lambda n, d: max([
    q for q in range(2, n) if\
    n-1-sum(d*(d-1)**(j-1) for j in range(1, q)) >= 0
])
Q = lambda n, d: k(n, d) - 1
R = lambda n, d: n - 1 - sum([d*(d-1)**(j-1) for j in range(1, k(n, d))])

# lower bound of sum of shortest path length
def sspl_lb(n, d):
    return n * (
        sum(j*d*(d-1)**(j-1) for j in range(1, k(n,d))) + k(n, d)*R(n,d)
    )

def sspl(G):
    p = nx.shortest_path_length(G)
    return sum(p[u][v] for u, v in product(G.nodes(), G.nodes()))

def make_cerf_tree_dfs(n, d, out):
    print('n,d,nid,eid,child0,child1,exp,lval', file=out)
    Gbase = build_base_graph(n, d)
    r_nodes = sorted([v for v in Gbase.nodes_iter() if Gbase.degree(v) < d])
    r_edges = [(u, v) for u in r_nodes for v in r_nodes if u < v]
    r_node_range_in_edges = [(
        min(i for i, (j, k) in enumerate(r_edges) if j == v or k == v),
        max(i for i, (j, k) in enumerate(r_edges) if j == v or k == v)
    ) for v in r_nodes]
    node_count = 0
    exp = '-'*len(r_edges)

    stack = [(0, Gbase, node_count, exp)]
    while len(stack) > 0:
        i, G, nid, exp = stack.pop()
        if i < len(r_edges):
            lval = '-'
        elif R(n, d) == 0 and nx.diameter(G) == Q(n, d) or\
             nx.diameter(G) == Q(n, d) + 1:
            lval = '1'
        else:
            lval = '0'

        if(i == len(r_edges)):
            print('{},{},{},{},,,{},{}'.format(
                n, d, nid, i, exp, lval),
                  file=out)
            continue

        # not add edge
        # if there are not vertices that exit frontier or
        # all exiting vertices satisfies degree constraint
        if all(G.degree(u) == d
               for u, (lo, hi) in zip(r_nodes, r_node_range_in_edges)\
               if i == hi):
            node_count += 1
            child_0 = node_count
            child_exp = list(exp)
            child_exp[i] = '0'
            child_exp = ''.join(child_exp)
            stack.append((i+1, G.copy(), child_0, child_exp))
        else:
            child_0 = ''

        # add edge
        v, w = r_edges[i]
        H = G.copy()
        H.add_edge(*r_edges[i])
        # if adjacent vertices does not exceed degree
        # and frontier constraint
        # and cycle constraint
        if all(H.degree(u) <= d for u in (v, w)) and\
           all(H.degree(u) == d
               for u, (lo, hi) in zip(r_nodes, r_node_range_in_edges)\
               if i == hi) and\
           (not nx.has_path(G, v, w) or\
            nx.shortest_path_length(G, v, w) >= 2*Q(n, d)):
            node_count += 1
            child_1 = node_count
            child_exp = list(exp)
            child_exp[i] = '1'
            child_exp = ''.join(child_exp)
            stack.append((i+1, H, child_1, child_exp))
        else:
            child_1 = ''

        print('{},{},{},{},{},{},{},{}'.format(
            n, d, nid, i, child_0, child_1, exp, lval),
              file=out)


if __name__ == '__main__':
    n, d = int(sys.argv[1]), int(sys.argv[2])
    Gbase = build_base_graph(n, d)
    r_nodes = sorted([v for v in Gbase.nodes_iter() if Gbase.degree(v) < d])
    r_edges = [(u, v) for u in r_nodes for v in r_nodes if u < v]
    with open('n{}-d{}.edge.csv'.format(n, d), 'w') as fp:
        print('n,d,eid,u,v', file=fp)
        for eid, (u, v) in enumerate(r_edges):
            print('{},{},{},{},{}'.format(n, d, eid, u, v),
                  file=fp)

    fp = open('n{}-d{}.tree.csv'.format(n, d), 'w')
    make_cerf_tree_dfs(n, d, fp)
    fp.close()
