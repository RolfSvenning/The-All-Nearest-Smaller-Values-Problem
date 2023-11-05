#ifndef ANSV2_PARALLELMINBINARYTREE_H
#define ANSV2_PARALLELMINBINARYTREE_H

#include "parlay/sequence.h"

// if left_i (right_i) is equal to -1 it means that it has no left (right) child
struct node {
    long val;
    long minVal;
    struct node * left_i;
    struct node * right_i;
    struct node * parent;
};

/**
 * returns a sequence of length 2n - 1 where the first n - 1 elements are -1
 * and the last n elements are each chosen uniform at random from the range [0...n-1]
 */
parlay::sequence<node> generateNotFixedMinBinaryTreeOnRandomInput(long n);

long parent(long i);

long child(long i, long c);

/**
 * Constructs a 'min binary tree' on the input sequence A assuming A is the output of
 * generateNotFixedMinBinaryTreeOnRandomInput(...).
 */
void fixNode(int i, parlay::sequence<long>& A, long n);

int main2(int argc, char* argv[]);

#endif //ANSV2_PARALLELMINBINARYTREE_H
