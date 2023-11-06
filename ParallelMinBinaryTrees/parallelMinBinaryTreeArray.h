#ifndef ANSV2_PARALLELMINBINARYTREE_H
#define ANSV2_PARALLELMINBINARYTREE_H

#include "parlay/sequence.h"


/**
 * returns a sequence of length 2n - 1 where the first n - 1 elements are -1
 * and the last n elements are each chosen uniform at random from the range [0...n-1]
 */
parlay::sequence<long> generateValues(long n);

parlay::sequence<long> createBinaryTreeForInput(parlay::sequence<long>& A);

long parent(long i);

long child(long i, long c);

/**
 * Constructs a 'min binary tree' on the input sequence A assuming A is the output of
 * generateValues(...).
 */
void fixNode(int i, parlay::sequence<long>& A, long n);

int main2(int argc, char* argv[]);

#endif //ANSV2_PARALLELMINBINARYTREE_H
