from itertools import izip, product
import networkx as nx
from build_base_graph import *

Q = lambda n, d: max([
    q for q in range(0, n) if\
    n-1-sum(d*(d-1)**(j-1) for j in range(1, q+1)) >= 0
])
R = lambda n, d: n - 1 - sum([d*(d-1)**(j-1) for j in range(1, Q(n, d))])

# lower bound of sum of shortest path length
def sspl_lb(n, d):
    return n * (
        sum(j*d*(d-1)**(j-1) for j in range(1, Q(n,d))) + Q(n, d)*R(n,d)
    )

def sspl(G):
    p = nx.shortest_path_length(G)
    return sum(p[u][v] for u, v in product(G.nodes(), G.nodes()))

def search_cerf_dfs(n, d):
    Gbase = build_base_graph(n, d)
    r_nodes = sorted([v for v in Gbase.nodes_iter() if Gbase.degree(v) < d])
    r_edges = [(u, v) for u in r_nodes for v in r_nodes if u < v]
    r_node_range_in_edges = [(
        min(i for i, (j, k) in enumerate(r_edges) if j == v or k == v),
        max(i for i, (j, k) in enumerate(r_edges) if j == v or k == v)
    ) for v in r_nodes]

    stack = [(0, Gbase)]
    while len(stack) > 0:
        i, G = stack.pop()
        if i == len(r_edges):
            yield G
            continue

        # not add edge
        # if there are not vertices that exit frontier or
        # all exiting vertices satisfies degree constraint
        if all(G.degree(u) == d
               for u, (lo, hi) in zip(r_nodes, r_node_range_in_edges)\
               if i == hi):
            stack.append((i+1, G.copy()))

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
            stack.append((i+1, H))

_Q = lambda n, d: depth(n-1, d) if n == n_node_btree(depth(n-1, d), d)\
     else depth(n-1, d) - 1
_R = lambda n, d: n - n_node_btree(_Q(n, d) - 1, d)

if __name__ == '__main__':
    for n, d in product(range(10, 30), range(3, 7)):
        if (n * d) % 2 == 1: continue
        print(' '.join(map(str, (n, d, Q(n, d), R(n, d)))))
    exit(0)
    n, d = 14, 3
    n_graphs = 1000
    for _, G in izip(xrange(n_graphs), search_cerf_dfs(n, d)):
        if(sspl(G) > sspl_lb(n, d)):
            print(G.edges())
            exit(0)
    """
    Note: Graph([
        (0, 1),
        (0, 2),
        (0, 3),
        (1, 4),
        (1, 5),
        (2, 6),
        (2, 7),
        (3, 8),
        (3, 9),
        (4, 8),
        (4, 6),
        (5, 10),
        (5, 7),
        (6, 11),
        (7, 12),
        (8, 13),
        (9, 10),
        (9, 12),
        (10, 13),
        (11, 12),
        (11, 13)
    ]) has girth 5 (> 2Q (2*2)), but has sspl 380 (lower bound: 378)
    diameter: 4
    """
