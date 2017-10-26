#!/usr/bin/env python
from __future__ import print_function

"""
(echo n,d,Q,R,sspl_lb,bdr,srt,sspl,node,time ;\
 ./exp_cmp_sort_param.py |\
 xargs --max-lines=1 --max-procs=4 ./exp_cmp_sort.out) >\
exp_cmp_sort_result.csv
"""
runs = 1
D = (3, 4, 5)
N = {
    3: list(range(4, 19, 2)) + list(range(22, 27, 2)),
    4: list(range(5, 13)),
    5: list(range(6, 11, 2)),
}

print('\n'.join([
    '{} {} {} {}'.format(bdr, srt, n, d)
    for _ in range(runs)
    for bdr, srt in [('basic', 'basic'), ('cycle', 'basic'),
                     ('cycle', 'sorted')]
    for d in D for n in N[d]
]))
