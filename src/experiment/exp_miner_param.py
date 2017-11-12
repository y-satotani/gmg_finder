#!/usr/bin/env python
from __future__ import print_function

"""
(echo n,d,Q,R,sspl_lb,sspl,edge,node,time ;\
 ./exp_miner_param.py |\
 xargs --max-lines=1 --max-procs=2 ./exp_miner.out) >\
exp_miner_result.csv
"""
D = (3, 4, 5)
N = {
    3: list(range(4, 30, 2)),
    4: list(range(5, 30)),
    5: list(range(6, 30, 2)),
}

print('\n'.join([
    '{} {}'.format(n, d)
    for d in D for n in N[d]
]))
