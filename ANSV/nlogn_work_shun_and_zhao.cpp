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

#include "nlogn_work_shun_and_zhao.h"
#include "parlay/parallel.h"
#include "../Glue/_aux.h"

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iostream>

using namespace std;

#define LEFT(i) ((i) << 1)
#define RIGHT(i) (((i) << 1) | 1)
#define PARENT(i) ((i) >> 1)

const int BLOCK_SIZE = 4; //TODO: only works for even block_size

inline int getLeft_opt(int **table, int depth, int n, int index, int start) {
  int value = table[0][index];
//  if (value == table[depth - 1][0]) return -1; ////TODO: commented out, assumes all values unique

  int cur = PARENT(start), d, dist = 2;
  for (d = 1; d < depth; d++) {
    if ((cur + 1) * dist > start + 1) cur --; //TODO: check this, should be start
    if (cur < 0) return -1;

    if (table[d][cur] > value) cur = PARENT(cur);
    else break;

    dist <<= 1;
  }

  for ( ; d > 0; d--) {
    if (table[d - 1][RIGHT(cur)] <= value) cur = RIGHT(cur);
    else cur = LEFT(cur);
  }
  if (cur == index) return -1;
  return cur;
}

// start: index from where to start the search (where last search found its match)
// index: original index of element looking for its match
// cur: index of the current root of subtree stored at this depth.
// depth: current level in tree (with bottom level being 1).
// dist: width of current subtree.
// cur*dist: first index covered by current subtree (since 0-indexed)
inline int getRight_opt(int **table, int depth, int n, int index, int start) {
  int value = table[0][index];
//  if (value == table[depth - 1][0]) return -1; //TODO: commented out, assumes all values unique

  int cur = PARENT(start), d, dist = 2;
  for (d = 1; d < depth; d++) {
//    if (index == 0) std::cout << cur << d << std::endl;
    if (cur * dist < start) cur ++; //checks if last parent was up to the left in which case move to the right in the tree
    if (cur * dist >= n) return -1; //current subtree past input //TODO: changed from  >= n - 1 to >= n

    if (table[d][cur] > value) cur = PARENT(cur); //check if subtree with match found
    else break;

    dist <<= 1; //increase "width" of current subtree
  }
//  if (index == 0) std::cout << "going down from cur: " << cur << std::endl;
  //going down the tree
  for ( ; d > 0; d--) {
//    if (index == 0) std::cout << d << " " << cur << std::endl;
    if (table[d - 1][LEFT(cur)] <= value) cur = LEFT(cur);
    else cur = RIGHT(cur);
  }
  if (cur == index) return -1;
  return cur;
}


void ComputeANSV_Linear(int a[], int nInner, std::array<VI, n> &L, std::array<VI, n> &R, int offset) {
  int i, top;
  int *stack = new int[nInner];

  for (i = 0, top = -1; i < nInner; i++) {
    while (top > -1 && a[stack[top]] > a[i]) top--;
    if (top == -1) {
//        leftElements[i] = -1;
        L[i + offset].ind = -1;
    }
    else {
//        leftElements[i] = stack[top] + offset;
        L[i + offset].ind = stack[top] + offset;
        L[i + offset].v = a[stack[top]];
    }
    stack[++top] = i;
  }

  for (i = nInner - 1, top = -1; i >= 0; i--) {
    while (top > -1 && a[stack[top]] > a[i]) top--;
    if (top == -1) {
//        rightElements[i] = -1;
        R[i + offset].ind = -1;
    }
    else {
//        rightElements[i] = stack[top] + offset;
        R[i + offset].ind = stack[top] + offset;
        R[i + offset].v = a[stack[top]];
    }
    stack[++top] = i;
  }
  delete stack;
}

inline int cflog2(int i) {
  int res = 0;

  i--;
  if (i >> 16) {
    res += 16;
    i >>= 16;
  } else i &= 0xffff;

  for (; i; i >>= 1) res++;
  return res;
}

std::tuple<std::array<VI, n>, std::array<VI, n>> ANSV_ShunZhao(std::array<long, n> A_) {
  std::cout << "BLOCK_SIZE: " << BLOCK_SIZE << std::endl;

  std::array<VI, n> L;
  std::array<VI, n> R;
  int a[n];
  for(int i=0; i < n; i++){
    a[i] = A_[i];
  }

  int l2 = cflog2(n);
  int depth = l2 + 1;
  int **table = new int*[depth];

  table[0] = a;
  int m = n;
  for (int i = 1; i < depth; i++) {
    m = (m + 1) / 2;
    table[i] = new int[m];
  }

  m = n;
  for (int d = 1; d < depth; d++) {
    int m2 = m / 2;

    parlay::parallel_for (0, m2, [&] (size_t i) {
      table[d][i] = min(table[d - 1][LEFT(i)], table[d - 1][RIGHT(i)]);
    });

    if (m % 2) {
      table[d][m2] = table[d - 1][LEFT(m2)];
    }

    m = (m + 1) / 2;
  }

  parlay::blocked_for(0, n, BLOCK_SIZE, [&] (size_t blockNumber, size_t i, size_t j) {
    ComputeANSV_Linear(a + i, j - i, L, R, i);

    int tmp = i;
    for (int k = i; k < j; k++) {
      if (L[k].ind == -1) {
        if (tmp != -1 && a[tmp] >= a[k]) {
          tmp = getLeft_opt(table, depth, n, k, tmp);
        }
//          leftI[k] = tmp;
          L[k].ind = tmp;
          if (tmp != -1) L[k].v = a[tmp];
      }
    }


    tmp = j - 1;
    //casting size_t to long to avoid default conversion of negative int to size_t which
    // will be large positive number since size_t is unsigned
    for (int k = j - 1; k >= (long)i; k--) {
      if (R[k].ind == -1) {
        if (tmp != -1 && a[tmp] >= a[k]) {
          tmp = getRight_opt(table, depth, n, k, tmp);
        }
//          rightI[k] = tmp;
          R[k].ind = tmp;
          if (tmp != -1) R[k].v = a[tmp];
      }
    }
//    std::cout << R[0].ind << "," << R[0].v << "<- (3)" << std::endl;
  });
  for (int i = 1; i < depth; i++) delete table[i];
  delete table;

  return {L,R};
}
