#!/bin/bash

#
# @(#) Run the stack/heap benchmarks
#

rm *.txt

make clean
make -f MO2
################################################################################
echo "Non filled allocation test (no memory init), O2"
################################################################################
export NDRX_BENCH_FILE=noinit2.txt
export NDRX_BENCH_CONFIGNAME="Stack alloc"
export LOOPS=10000000
export NDRX_BENCH_TITLE="No init heap vs stack benchmark ($LOOPS loops per size), -O2"
export NDRX_BENCH_X_LABEL="Bytes alloced (10 mixed blocks)"
export NDRX_BENCH_Y_LABEL="Milliseconds spent"
export NDRX_BENCH_OUTFILE="noinit2.png"

echo "Non filled allocation test / stack ..."

./alloct s n $LOOPS 2 || exit 1

export NDRX_BENCH_CONFIGNAME="Heap alloc"

echo "Non filled allocation test / heap ..."

./alloct h n $LOOPS 2 || exit 2

R -f genchart.r


################################################################################
echo "Filled allocation test, O2"
################################################################################

export NDRX_BENCH_FILE=filled2.txt
export NDRX_BENCH_CONFIGNAME="Stack alloc"
export LOOPS=100000
export NDRX_BENCH_TITLE="Fill heap vs stack benchmark ($LOOPS loops per size), -O2"
export NDRX_BENCH_X_LABEL="Bytes alloced (10 mixed blocks)"
export NDRX_BENCH_Y_LABEL="Milliseconds spent"
export NDRX_BENCH_OUTFILE="filled2.png"


echo "Filled allocation test / stack ..."

./alloct s f $LOOPS 2 || exit 3

export NDRX_BENCH_CONFIGNAME="Heap alloc"

echo "Filled allocation test / heap ..."

./alloct h f $LOOPS 2 || exit 4

R -f genchart.r

################################################################################
echo "Non filled allocation test (no memory init)"
################################################################################
make clean
make

export NDRX_BENCH_FILE=noinit1.txt
export NDRX_BENCH_CONFIGNAME="Stack alloc"
export LOOPS=10000000
export NDRX_BENCH_TITLE="No init heap vs stack benchmark ($LOOPS loops per size), -O1"
export NDRX_BENCH_X_LABEL="Bytes alloced (10 mixed blocks)"
export NDRX_BENCH_Y_LABEL="Milliseconds spent"
export NDRX_BENCH_OUTFILE="noinit1.png"

echo "Non filled allocation test / stack ..."

./alloct s n $LOOPS 1 || exit 1

export NDRX_BENCH_CONFIGNAME="Heap alloc"

echo "Non filled allocation test / heap ..."

./alloct h n $LOOPS 1 || exit 2

R -f genchart.r


################################################################################
echo "Filled allocation test"
################################################################################

export NDRX_BENCH_FILE=filled1.txt
export NDRX_BENCH_CONFIGNAME="Stack alloc"
export LOOPS=100000
export NDRX_BENCH_TITLE="Fill heap vs stack benchmark ($LOOPS loops per size), -O1"
export NDRX_BENCH_X_LABEL="Bytes alloced (10 mixed blocks)"
export NDRX_BENCH_Y_LABEL="Milliseconds spent"
export NDRX_BENCH_OUTFILE="filled1.png"


echo "Filled allocation test / stack ..."

./alloct s f $LOOPS 1 || exit 3

export NDRX_BENCH_CONFIGNAME="Heap alloc"

echo "Filled allocation test / heap ..."

./alloct h f $LOOPS 1 || exit 4

R -f genchart.r
