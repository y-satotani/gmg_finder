from __future__ import print_function, division
from math import floor, log
import networkx as nx

depth = lambda v, d: 0 if v == 0 else\
        int(log((v-1)*(d-2)/d+1, d-1))+1

# number of node of balanced tree
n_node_btree = lambda l, d: (1+d*((d-1)**l-1)//(d-2))

parent_of = lambda v, d: -1 if v == 0 else\
            0 if v <= d else\
            (v-n_node_btree(depth(v,d)-1,d))//(d-1) +\
            n_node_btree(depth(v,d)-2,d)

def build_base_graph(n, d):
    n_node_connect = n if n == n_node_btree(depth(n-1, d), d) else\
                     n_node_btree(depth(n-1, d) - 1, d)
    G = nx.Graph()
    G.add_nodes_from(range(n))
    G.add_edges_from((parent_of(v, d), v)
                     for v in range(1, n_node_connect))
    return G

if __name__ == '__main__':
    print(depth(9, 3))
    print(build_base_graph(16, 3).edges())
    print(build_base_graph(22, 3).edges())
    print(build_base_graph(36, 5).edges())
