#!/usr/bin/env python
from __future__ import print_function

"""
(echo n,d,Q,R,sspl_lb,bdr,mgr,sspl,node,time ;\
 ./exp_cmp_algo_param.py |\
 xargs --max-lines=1 --max-procs=4 ./exp_cmp_algo.out) >\
exp_cmp_algo_result.csv
"""
runs = 10
D = (3, 4, 5)
N = {
    3: list(range(4, 25, 2)),
    4: list(range(5, 13)),
    5: list(range(6, 15, 2)),
}
Nsmall = {
    3: list(range(4, 17, 2)),
    4: list(range(5, 11)),
    5: list(range(6, 9, 2)),
}

print('\n'.join([
    '{} {} {} {}'.format(bdr, mgr, n, d)
    for _ in range(runs)
    for bdr in ('basic', 'cycle', 'stree')
    for mgr in ('basic', 'minmax')
    for d in D for n in Nsmall[d]
]))
