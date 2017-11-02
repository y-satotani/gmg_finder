#!/usr/bin/env python
from __future__ import print_function

"""
(echo n,d,Q,R,sspl_lb,mgr,sspl,edge,node,time ;\
 ./exp_cmp_minmax_mtr_param.py |\
 xargs --max-lines=1 --max-procs=4 ./exp_cmp_minmax_mtr.out) >\
exp_cmp_algo_result.csv
"""
runs = 1
d = 3
N = list(range(4, 20, 2))

print('\n'.join([
    '{} {} {}'.format(mgr, n, d)
    for _ in range(runs)
    for mgr in ('basic', 'minmax', 'matrix')
    for n in N
]))
