#!/usr/bin/env python
import argparse as ap
import networkx as nx
import matplotlib.pyplot as plt

parser = ap.ArgumentParser()
parser.add_argument('-i', '--input', type=str)
parser.add_argument('-o', '--output', type=str)
parser.add_argument('--solid-dash', action='store_true')
args = parser.parse_args()

G = nx.read_edgelist(args.input)
pos = nx.spring_layout(G)
nx.draw_networkx_nodes(G, pos, G.nodes(), node_color='royalblue')
if args.solid_dash:
    tree_edge = [
        (v, str(min(map(int, G.neighbors(v)))))
        for v in G.nodes_iter() if v > 1
    ]
    cycle_edge = list(set(G.edges()).difference(set(tree_edge)))
    nx.draw_networkx_edges(G, pos, tree_edge, style='solid')
    nx.draw_networkx_edges(G, pos, cycle_edge, style='dashed')
else:
    nx.draw_networkx_edges(G, pos, G.edges(), style='solid')
nx.draw_networkx_labels(G, pos, dict(zip(G.nodes(), G.nodes())))
plt.axis('off')
plt.savefig(args.output, bbox_inches='tight')

