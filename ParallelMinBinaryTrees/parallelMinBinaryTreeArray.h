#ifndef ANSV2_PARALLELMINBINARYTREE_H
#define ANSV2_PARALLELMINBINARYTREE_H

#include "parlay/sequence.h"


/**
 * returns a sequence of length 2n - 1 where the first n - 1 elements are -1
 * and the last n elements are each chosen uniform at random from the range [0...n-1]
 */
parlay::sequence<long> generateValues(long n);

long treeIndexToArrayIndex(long i, long d);

std::tuple<parlay::sequence<long>,long> createBinaryTreeForInput(parlay::sequence<long>& A);

long parent(long i);

long child(long i, long c);

/**
 * Constructs a 'min binary tree' on the input sequence T assuming T is the output of
 * generateValues(...).
 */
void convertToMinBinary(long i, parlay::sequence<long>&T, long n);

int main3(int argc, char* argv[]);

#endif //ANSV2_PARALLELMINBINARYTREE_H
