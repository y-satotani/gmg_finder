#!/usr/bin/env python
from __future__ import print_function

"""
(echo n,d,Q,R,sspl_lb,ginitr,sorted,sinitr,test,n_graph,n_edge,n_state,time ;\
 ./exp_cmp_algo_enum_param.py |\
 xargs --max-lines=1 --max-procs=4 ./exp_cmp_algo_enum.out) >\
cmp-algo-enum.csv
"""
runs = 1
D = (3, 4)
N = {
    3: list(range(4, 19, 2)),
    4: list(range(5, 12)),
}

mtds = [
    (g, 'basic', s)
    for g in ('basic', 'cycle', 'stree')
    for s in ('basic',)
] + [
    ('cycle', 'sorted', s)
    for s in ('basic',)
]

print('\n'.join([
    '{} {} {} {} {}'.format(bdr, srt, mgr, n, d)
    for _ in range(runs)
    for bdr, srt, mgr in mtds
    for d in D for n in N[d]
]))
