#!/usr/bin/env python
from __future__ import print_function
import sys
import time
import signal
import argparse
import functools

""" example:
./exp_miner_param.py -n 40 -d 5 -t 3600 \
-i ../../docs/res/data/miner.csv

./exp_miner_param.py --nmin 10 --nmax 20 --dmin 5 --dmax 7 -t 3600 \
-i ../../docs/res/data/miner.csv

( echo "n,d,Q,R,sspl_lb,sspl,edge,state,time" ; ./exp_miner_param.py |\
xargs -L1 -P4 ./exp_miner_timeout.py ) > result.csv
"""

def get_arguments():
    parser = argparse.ArgumentParser(description='')
    parser.add_argument('-n', type=int)
    parser.add_argument('--nmin', type=int)
    parser.add_argument('--nmax', type=int)
    parser.add_argument('-d', type=int)
    parser.add_argument('--dmin', type=int)
    parser.add_argument('--dmax', type=int)
    parser.add_argument('-i', type=str, nargs='*', default=[])
    parser.add_argument('-t', type=int)
    return parser.parse_args()

def make_params(args):
    if args.n:
        nmin, nmax = 4, args.n
    elif args.nmin and args.nmax:
        nmin, nmax = args.nmin, args.nmax
    else:
        pass
    if args.d:
        dmin, dmax = 3, args.d
    elif args.dmin and args.dmax:
        dmin, dmax = args.dmin, args.dmax
    else:
        pass

    params = set()
    for d in range(dmin, dmax+1):
        for n in range(max(d+1, nmin), nmax+1):
            if n * d % 2 == 0:
                params.add((n, d))
    for f in args.i:
        try:
            with open(f, 'r') as fp:
                table = fp.read().splitlines()[1:]
                for row in table:
                    n, d = list(map(int, row.split(',')[:2]))
                    if (n, d) in params:
                        params.remove((n, d))
        except:
            print('file {} not found'.format(f), file=sys.stderr)
    return params

def main():
    args = get_arguments()
    for n, d in make_params(args):
        print(
            '-n {} -d {} -t {}'.format(n, d, args.t) if args.t else\
            '-n {} -d {}'.format(n, d),
            file=sys.stdout
        )

if __name__ == '__main__':
    main()
