#!/usr/bin/env python
from __future__ import print_function

"""
(echo n,d,Q,R,sspl_lb,bdr,mgr,srt,n_graph,sspl_max,sspl_min,edge,node,time ;\
 ./exp_cmp_algo_full_param.py |\
 xargs --max-lines=1 --max-procs=4 ./exp_cmp_algo_full.out) >\
exp_cmp_algo_full_result.csv
"""
runs = 1
D = (3,)
N = {
    3: list(range(4, 17, 2)),
    #4: list(range(5, 11)),
    #5: list(range(6, 9, 2)),
}

mtd = [
    ('basic', 'basic', 'basic'),
    ('cycle', 'basic', 'sorted'),
    ('stree', 'basic', 'basic'),
]

print('\n'.join([
    '{} {} {} {} {}'.format(bdr, mgr, srt, n, d)
    for _ in range(runs)
    for bdr, mgr, srt in mtd
    for d in D for n in N[d]
]))
