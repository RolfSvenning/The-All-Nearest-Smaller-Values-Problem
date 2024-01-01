// This code is part of the 15418 course project: Implementation and Comparison
// of Parallel LZ77 and LZ78 Algorithms and DCC 2013 paper: Practical Parallel
// Lempel-Ziv Factorization
// Copyright (c) 2012 Fuyao Zhao, Julian Shun
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights (to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to
// the following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
// LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
// OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include <iostream>
#include "nlogn_work_shun_and_zhao.h"
#include "shunZhaoOriginal.h"
#include "parlay/parallel.h"
#include "../Glue/_aux.h"
#include "parlay/primitives.h"


using namespace std;
using namespace parlay;

#define LEFT(i) ((i) << 1)
#define RIGHT(i) (((i) << 1) | 1)
#define PARENT(i) ((i) >> 1)


double ANSV_ShunZhao(long *A, long n, long *L, long *R, long blockSize) {
    internal::timer t("Time");
    t.start();
    auto [table, depth] = createBinaryTree(A, n);
    t.next("creating binary tree");

    blocked_for(0, n, blockSize, [&] (size_t blockNumber, size_t i, size_t j) {
        ComputeANSV_Linear(A + i, j - i, L + i, R + i, i);
        long tmp = i;
        for (long k = i; k < j; k++) {
            if (L[k] == -1) {
                if ((tmp != -1 && A[tmp] > A[k]) or k == i) {
                    tmp = getLeft_opt(table, depth, n, k, tmp);
                }
                L[k] = tmp;
            }
        }

        tmp = j - 1;
        // casting size_t to long to avoid default conversion of negative int to size_t which
        // will be large positive number since size_t is unsigned
        for (long k = j - 1; k >= (long)i; k--) {
            if (R[k] == -1) {
                if ((tmp != -1 && A[tmp] > A[k]) or k == j - 1) {
                    tmp = getRight_opt(table, depth, n, k, tmp);
                }
                R[k] = tmp;
            }
        }
    });

    delete[] table;

    return t.total_time();
}

