#!/usr/bin/env python
from __future__ import print_function

"""
(echo n,d,Q,R,sspl_lb,bdr,mgr,srt,sspl,edge,node,time ;\
 ./exp_cmp_algo_param.py |\
 xargs --max-lines=1 --max-procs=4 ./exp_cmp_algo.out) >\
exp_cmp_algo_result.csv
"""
runs = 10
D = (3, 4, 5)
N = {
    3: list(range(4, 17, 2)),
    4: list(range(5, 11)),
    5: list(range(6, 9, 2)),
}

mtds = [
    ('basic', 'basic', 'basic'),
    ('basic', 'minmax', 'basic'),
    ('cycle', 'basic', 'sorted'),
    ('cycle', 'minmax', 'sorted'),
    ('stree', 'basic', 'basic'),
    ('stree', 'minmax', 'basic')
]

print('\n'.join([
    '{} {} {} {} {}'.format(bdr, mgr, srt, n, d)
    for _ in range(runs)
    for bdr, mgr, srt in mtds
    for d in D for n in N[d]
]))
