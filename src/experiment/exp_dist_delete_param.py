#!/usr/bin/env python
from __future__ import print_function
from random import randint
"""
(echo n,p-or-m,type,seed,m,test,time-igraph,time ;\
 ./exp_dist_delete_param.py |\
 xargs --max-lines=1 --max-procs=4 ./exp_dist_delete.out) >\
exp_dist_delete_result.csv
"""
runs = 100
N = (10, 50, 100, 300, 600, 1000, 1500, 2000)
M = (3, 6, 10, 15, 20)
P = (0.1, 0.3, 0.6, 0.9)
params = [
    ('random', n, p, randint(0, 2**32-1))
    for n in N
    for p in P
] + [
    ('scale-free', n, m, randint(0, 2**32-1))
    for n in N
    for m in M
    if n > m
]

print('\n'.join([
    '{} {} {} {}'.format(*p)
    for _ in range(runs)
    for p in params
]))
