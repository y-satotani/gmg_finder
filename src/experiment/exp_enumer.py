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
./exp_miner.py -n 40 -d 5 -t 3600 \
-i ../../document/resource/table/miner.csv \
-o out.csv
"""

def get_arguments():
    parser = argparse.ArgumentParser(description='')
    parser.add_argument('-n', type=int, required=True)
    parser.add_argument('-d', type=int, required=True)
    parser.add_argument('-i', type=str, nargs='*', default=[])
    parser.add_argument('-o', type=str)
    parser.add_argument('-t', type=int)
    return parser.parse_args()

def make_params(args):
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
    return params

def write_result(args, rows):
    rows = [r for r in rows if r]
    header = 'n,d,Q,R,sspl_lb,alg,sspl,edge,node,time'
    out = open(args.o, 'w') if args.o else sys.stdout
    print('\n'.join([header]+rows), file=out)
    out.close()

def mgr_init():
    signal.signal(signal.SIGINT, signal.SIG_IGN)

def run_miner(n, d, t, n_proc, rows):
    proc = subprocess.Popen(
        ['./exp_miner.out', str(n), str(d)],
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE
    )
    try:
        out, err = proc.communicate(timeout=t)
        rows.append(out.strip())
        sys.stderr.write('pair {}, {} finished\n'.format(n, d))
        sys.stderr.flush()
    except subprocess.TimeoutExpired:
        proc.kill()
        sys.stderr.write('pair {}, {} timeout\n'.format(n, d))
        sys.stderr.flush()
    except KeyboardInterrupt:
        proc.kill()
    finally:
        n_proc.value -= 1

def main():
    args = get_arguments()
    params = make_params(args)
    n_cpu = multiprocessing.cpu_count()
    manager = multiprocessing.managers.SyncManager()
    manager.start(mgr_init)
    processes = []

    n_proc = multiprocessing.Value('i', 0)
    rows = manager.list()

    try:
        for n, d in params:
            while n_proc.value == n_cpu:
                time.sleep(1)
            n_proc.value += 1
            p = multiprocessing.Process(target=run_miner,
                                       args=(n, d, args.t, n_proc, rows))
            p.start()
            processes.append(p)
        try:
            for p in processes:
                p.join()
        except KeyboardInterrupt:
            pass
        finally:
            write_result(args, rows)
    finally:
        manager.shutdown()

if __name__ == '__main__':
    main()
