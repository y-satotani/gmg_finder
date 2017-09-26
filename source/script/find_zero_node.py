#!/usr/bin/env python
from __future__ import print_function
import sys

n, d = int(sys.argv[1]), int(sys.argv[2])
filename = 'n{}-d{}.tree.csv'.format(n, d)
def conv_tuple(line):
    t = line.split(',')
    return (int(t[2]),                         # nid
            int(t[3]),                         # eid
            int(t[4]) if t[4] else None,       # child0
            int(t[5]) if t[5] else None,       # child1
            int(t[7]) if t[7] != '-' else None # lval
    )

with open(filename) as fp:
    data = []
    for line in fp.read().splitlines()[1:]:
        data.append(conv_tuple(line))
data = sorted(data, key=lambda t: t[0])
is_zero_node = [False]*len(data)
n_descendant = [0]*len(data)

stack = [(0, 0)]
while len(stack) > 0:
    phase, nid = stack.pop()
    child0 = data[nid][2]
    child1 = data[nid][3]
    lval = data[nid][4]

    if child0 is None and child1 is None:
        is_zero_node[nid] = lval == 0 or lval == None
        n_descendant[nid] = 0
    elif phase == 0:
        children = []
        if child0 != None:
            children.append((0, child0))
        if child1 != None:
            children.append((0, child1))
        stack.extend([(1, nid)] + children)
    else:
        is_zero_node[nid] = lval == 0 or\
                            (child0 is None or is_zero_node[child0]) and\
                            (child1 is None or is_zero_node[child1])
        n_descendant[nid] = (n_descendant[child0]\
                             if child0 is not None else 0) +\
                            (n_descendant[child1]\
                             if child1 is not None else 0) +\
                                1

outfilename = 'n{}-d{}.zero.csv'.format(n, d)
with open(outfilename, 'w') as out:
    print('n,d,nid,ndesc', file=out)
    for t in sorted(
            filter(lambda t: is_zero_node[t[0]], data),
            key=lambda t: n_descendant[t[0]],
            reverse=True
    ):
        print('{},{},{},{}'.format(
            n, d, t[0], n_descendant[t[0]]),
              file=out)
