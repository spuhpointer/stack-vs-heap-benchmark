# Stack VS Heap Benchmark

## Overview

It is long standing debate which memory allocation technique is faster stack
or heap. Heap allocation should take longer time because of fact that it requires
to manage the pool of various size chunks in memory. Where stack does not requires
any management, just change the stack pointer to reserve some memory block and
that's it.

At this repository the benchmark is presented. Where code performs following
actions:

1. Allocate stack memory with out initializing it
VS
2. Allocate heap memory with out initializing it
3. Allocate stack memory with initialization
VS
4. Allocate heap memory with initialization

Tests are performed in two modes: with GCC -O1 and -O2 optimizations.

Basic idea to have time benchmarks at certain memory chunk allocation (10x different sizes)
in the loop. The measurement result is time taken for number of allocation attempts
with different total chunk sizes.


# Tests

Test machine is: Intel(R) Core(TM) i7-6600U CPU, Linux 64 bit, 4.15.0-50-generic, Spectre and
Meltdown patches disabled.

## Stack VS Heap - No INIT results -O1

![Alt text](noinit1.png?raw=true "Stack VS Heap O1, no init")

## Stack VS Heap - With INIT results -O1

![Alt text](filled1.png?raw=true "Stack VS Heap O1, have init")

## Stack VS Heap - No INIT results -O2

![Alt text](noinit2.png?raw=true "Stack VS Heap O2, no init")

## Stack VS Heap - With INIT results -O2

![Alt text](filled2.png?raw=true "Stack VS Heap O2, have init")

# Results

In the results we see that in case of no-init, stack is signficantly faster,
but needs to take in account that loops are about 10M where in each position
10 allocations are made.

In case of memory init (e.g. software allocates some memory block and fills with
some data), there is no significant difference in these two approaches).

Thus when writing software that actually uses the memory allocated, there is question
are there real need for stack allocation approach?









