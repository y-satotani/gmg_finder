#!/usr/bin/env python
from __future__ import print_function

"""
(echo n,d,Q,R,sspl_lb,bdr,srt,mgr,sspl,edge,node,time ;\
 ./exp_cmp_algo_param.py |\
 xargs --max-lines=1 --max-procs=4 ./exp_cmp_algo.out) >\
cmp-algo.csv
"""
runs = 10
D = (3, 4)
N = {
    3: list(range(4, 17, 2)),
    4: list(range(5, 12)),
}

mtds = [
    (g, 'basic', s)
    for g in ('basic', 'cycle', 'stree')
    for s in ('basic', 'matrix', 'minmax')
] + [
    ('cycle', 'sorted', s)
    for s in ('basic', 'matrix', 'minmax')
]

print('\n'.join([
    '{} {} {} {} {}'.format(bdr, srt, mgr, n, d)
    for _ in range(runs)
    for bdr, srt, mgr in mtds
    for d in D for n in N[d]
]))
