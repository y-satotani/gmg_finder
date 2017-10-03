#!/usr/bin/env python
from __future__ import print_function
from build_base_graph import *

# xargs --max-args=1 sh -c

print(
    ' '.join(map(

    lambda t:\
        ('"time -p bin/{prog}.out ' +\
         '-o result_tconj/d{d}-n{n}-{prog}.elist {n} {d} '+\
         '2> result_tconj/d{d}-n{n}-{prog}.time"')\
    .format(n=t[0], d=t[1], prog=t[2]),

    [(n, d, prog)
     for n in range(23)
     for d in range(3, 6)
     for prog in ['naive_dfs', 'naive_dfs_tree_conjecture']
     if n * d % 2 == 0 and n > d
    ]

    ))
)

