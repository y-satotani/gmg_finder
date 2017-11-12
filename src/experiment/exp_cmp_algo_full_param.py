#!/usr/bin/env python
from __future__ import print_function

"""
(echo n,d,Q,R,sspl_lb,bdr,srt,mgr,n_graph,sspl_max,sspl_min,edge,node,time ;\
 ./exp_cmp_algo_full_param.py |\
 xargs --max-lines=1 --max-procs=4 ./exp_cmp_algo_full.out) >\
cmp-algo-full.csv
"""
runs = 1
d = 3
#N = list(range(4, 17, 2))
N = list(range(4, 11, 2))

mtd = [
    ('basic', 'basic', 'basic'),
    ('cycle', 'basic', 'sorted'),
    ('stree', 'basic', 'basic'),
]

does_sort = lambda g: g == 'cycle'
mtds = [
    (g, 'sorted' if does_sort(g) else 'basic', s)
    for g in ('basic', 'cycle', 'stree')
    for s in ('basic', 'matrix', 'minmax')
]

print('\n'.join([
    '{} {} {} {} {}'.format(bdr, srt, mgr, n, d)
    for _ in range(runs)
    for bdr, srt, mgr in mtds
    for n in N
]))
