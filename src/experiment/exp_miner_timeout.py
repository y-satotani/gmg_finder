#!/usr/bin/env python
from __future__ import print_function
import sys
import time
import signal
import argparse
import functools
import multiprocessing
import multiprocessing.managers
if sys.version_info < (3,):
    import subprocess32 as subprocess
else:
    import subprocess

""" example:
./exp_miner_timeout.py -n 40 -d 5 -t 3600
"""

def get_arguments():
    parser = argparse.ArgumentParser(description='')
    parser.add_argument('-n', type=int, required=True)
    parser.add_argument('-d', type=int, required=True)
    parser.add_argument('-t', type=int)
    return parser.parse_args()

def write_result(args, rows):
    rows = [r for r in rows if r]
    header = 'n,d,Q,R,sspl_lb,sspl,edge,state,time'
    out = open(args.o, 'w') if args.o else sys.stdout
    print('\n'.join([header]+rows), file=out)
    out.close()

def run_miner(n, d, t):
    proc = subprocess.Popen(
        ['./exp_miner.out', str(n), str(d)],
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE
    )
    try:
        out, err = proc.communicate(timeout=t)
        sys.stdout.write('{}\n'.format(out.strip()))
        sys.stdout.flush()
        sys.stderr.write('n={}, d={} finished\n'.format(n, d))
        sys.stderr.flush()
    except subprocess.TimeoutExpired:
        proc.kill()
        sys.stderr.write('n={}, d={} timeout\n'.format(n, d))
        sys.stderr.flush()

def main():
    args = get_arguments()
    run_miner(args.n, args.d, args.t)

if __name__ == '__main__':
    main()
