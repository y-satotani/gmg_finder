#!/usr/bin/env python
from __future__ import print_function
from build_base_graph import *

# xargs --max-args=6 time -o

print(
    ' '.join(map(

    lambda t:\
        'n{n}.{prog}.time bin/{prog}.out -o result_r2/n{n}.{prog}.elist {n} 3'\
    .format(n=n_node_btree(t[0], 3)+2, prog=t[1]),

    [(q, prog)
     for q in range(2, 3)
     for prog in ['naive_dfs', 'naive_dfs_r2']
    ]

    ))
)

