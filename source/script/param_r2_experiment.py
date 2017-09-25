#!/usr/bin/env python
from __future__ import print_function
from build_base_graph import *

# xargs --max-args=1 sh -c

print(
    ' '.join(map(

    lambda t:\
        ('"time -p bin/{prog}.out ' +\
         '-o result_r2/n{n}.{prog}.elist {n} 3 '+\
         '2> result_r2/n{n}.{prog}.time"')\
    .format(n=n_node_btree(t[0], 3)+2, prog=t[1]),

    [(q, prog)
     for q in range(2, 6)
     for prog in ['naive_dfs', 'naive_dfs_r2']
    ]

    ))
)

