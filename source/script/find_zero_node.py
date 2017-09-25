#!/usr/bin/env python
from __future__ import print_function
import sys

n, d = int(sys.argv[1]), int(sys.argv[2])
filename = 'n{}-d{}.tree.csv'.format(n, d)
def conv_tuple(line):
    t = line.split(',')
    return (int(t[2]),
            int(t[3]),
            int(t[4]) if t[4] else None,
            int(t[5]) if t[5] else None,
            int(t[7]) if t[7] != '-' else None
    )

with open(filename) as fp:
    data = []
    for line in fp.read().splitlines()[1:]:
        data.append(conv_tuple(line))
data = sorted(data, key=lambda t: t[0])
is_zero_node = [1]*len(data)

stack = [(0, 0)]
while len(stack) > 0:
    phase, nid = stack.pop()
    if phase == 0:
        pass
    else:
        pass

outfilename = 'n{}-d{}.zero.csv'.format(n, d)
with open(outfilename, 'w') as out:
    print('n,d,nid', out)
    for _, t in sorted(filter(lambda t: t[0], zip(is_zero_node, data)),
                       key=lambda t: t[1][1]):
        print('{},{},{}'.format(n, d, t[0]))
