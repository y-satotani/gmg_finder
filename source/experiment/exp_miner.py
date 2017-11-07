#!/usr/bin/env python
from __future__ import print_function
import sys
import argparse
import multiprocessing
if sys.version_info < (3,):
    import subprocess32 as subprocess
else:
    import subprocess

# example:
# ./exp_miner.py -n 40 -d 5 -t 3600 -i ../../resource/table/miner.csv \
#   -o out.csv

def get_arguments():
    parser = argparse.ArgumentParser(description='')
    parser.add_argument('-n', type=int, required=True)
    parser.add_argument('-d', type=int, required=True)
    parser.add_argument('-i', type=str, nargs='*', default=[])
    parser.add_argument('-o', type=str)
    parser.add_argument('-t', type=int)
    return parser.parse_args()

def run_miner(args):
    n, d, t = args
    proc = subprocess.Popen(
        ['./exp_miner.out', str(n), str(d)],
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE
    )
    try:
        out, err = proc.communicate(timeout=t)
        out = out.strip()
    except subprocess.TimeoutExpired:
        out, err = None, None
    return out

def main():
    args = get_arguments()
    params = set()
    for d in range(3, args.d+1):
        for n in range(d+1, args.n+1):
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
    params = [(n, d, args.t) for n, d in params]
    pool = multiprocessing.Pool()
    rows = pool.map(run_miner, params)
    rows = [r for r in rows if r is not None]
    header = 'n,d,Q,R,sspl_lb,sspl,edge,node,time'
    if args.o is None:
        out = sys.stdout
    else:
        out = open(args.o, 'w')
    print('\n'.join([header]+rows), file=out)
    out.close()

if __name__ == '__main__':
    main()
