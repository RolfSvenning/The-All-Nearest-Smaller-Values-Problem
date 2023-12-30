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



//int getLeft_opt(long **table, long depth, long n, long index, long start) {
//  long value = table[0][index];
//  if (value == table[depth - 1][0]) return -1;
//
//  long cur = PARENT(start), d, dist = 2;
//  for (d = 1; d < depth; d++) {
//    if ((cur + 1) * dist > start + 1) cur --; //TODO: check this, should be start
//    if (cur < 0) return -1;
//
//    if (table[d][cur] > value) cur = PARENT(cur);
//    else break;
//
//    dist <<= 1;
//  }
//
//  for ( ; d > 0; d--) {
//    if (table[d - 1][RIGHT(cur)] <= value) cur = RIGHT(cur);
//    else cur = LEFT(cur);
//  }
//  if (cur == index) return -1;
//  return cur;
//}

// start: index from where to start the search (where last search found its match)
// index: original index of element looking for its match
// cur: index of the current root of subtree stored at this depth.
// depth: current level in tree (with bottom level being 1).
// dist: width of current subtree.
// cur*dist: first index covered by current subtree (since 0-indexed)
//long getRight_opt(long **table, long depth, long n, long index, long start) {
//  long value = table[0][index];
//  if (value == table[depth - 1][0]) return -1;
//
//  long cur = PARENT(start), d, dist = 2;
//  for (d = 1; d < depth; d++) {
//    if (cur * dist < start) cur ++; //checks if last parent was up to the left in which case move to the right in the tree
//    if (cur * dist >= n) return -1; //current subtree past input
//
//    if (table[d][cur] > value) cur = PARENT(cur); //check if subtree with match found
//    else break;
//
//    dist <<= 1; //increase "width" of current subtree
//  }
//  //going down the tree
//  for ( ; d > 0; d--) {
//    if (table[d - 1][LEFT(cur)] <= value) cur = LEFT(cur);
//    else cur = RIGHT(cur);
//  }
//  if (cur == index) return -1;
//
//  return cur;
//}


//void ComputeANSV_Linear(long a[], long n, long leftElements[], long rightElements[], long offset) {
//    long i, top;
//    long *stack = new long[n];
//
//    for (i = 0, top = -1; i < n; i++) {
//        while (top > -1 && a[stack[top]] > a[i]) top--;
//        if (top == -1) leftElements[i] = -1;
//        else leftElements[i] = stack[top] + offset;
//        stack[++top] = i;
//    }
//
//    for (i = n - 1, top = -1; i >= 0; i--) {
//        while (top > -1 && a[stack[top]] > a[i]) top--;
//        if (top == -1) rightElements[i] = -1;
//        else rightElements[i] = stack[top] + offset;
//        stack[++top] = i;
//    }
//    delete[] stack;
//}

//inline long cflog2(int i) {
//  long res = 0;
//
//  i--;
//  if (i >> 16) {
//    res += 16;
//    i >>= 16;
//  } else i &= 0xffff;
//
//  for (; i; i >>= 1) res++;
//  return res;
//}

// TODO: remember to delete in code when using!
tuple<long **, long> createBinaryTree(long *A, long n) {
    long l2 = cflog2(n);
    long depth = l2 + 1;
    long **table = new long*[depth];
    table[0] = A;
    long m = n;
    for (long i = 1; i < depth; i++) {
        m = (m + 1) / 2;
        table[i] = new long[m];
    }

    m = n;
    for (long d = 1; d < depth; d++) {
        long m2 = m / 2;

        parallel_for (0, m2, [&] (size_t i) {
            table[d][i] = min(table[d - 1][LEFT(i)], table[d - 1][RIGHT(i)]);
        });

        if (m % 2) table[d][m2] = table[d - 1][LEFT(m2)];
        m = (m + 1) / 2;
    }

  return {table, depth};
}

//tuple<sequence<long>, sequence<long>, float> ANSV_ShunZhao(sequence<long> &A, long blockSize){
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

