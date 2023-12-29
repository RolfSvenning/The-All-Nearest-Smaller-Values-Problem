//
// Created by Rolf on 12/29/2023.
//

#include <iostream>
#include "shunZhaoOriginal.h"
#include "parlay/primitives.h"


using namespace std;
using namespace parlay;

#define LEFT(i) ((i) << 1)
#define RIGHT(i) (((i) << 1) | 1)
#define PARENT(i) ((i) >> 1)


inline long getLeft_opt(long **table, long depth, long n, long index, long start) {
    long value = table[0][index];
    if (value == table[depth - 1][0]) return -1;

    long cur = PARENT(start), d, dist = 2;
    for (d = 1; d < depth; d++) {
        if ((cur + 1) * dist > start + 1) cur --;  //TODO: changed from index to start
        if (cur < 0) return -1;

        if (table[d][cur] >= value) cur = PARENT(cur);
        else break;

        dist <<= 1;
    }

    for ( ; d > 0; d--) {
        if (table[d - 1][RIGHT(cur)] < value) cur = RIGHT(cur);
        else cur = LEFT(cur);
    }
    return cur;
}

inline long getRight_opt(long **table, long depth, long n, long index, long start) {
    long value = table[0][index];
    if (value == table[depth - 1][0]) return -1;

    long cur = PARENT(start), d, dist = 2;
    for (d = 1; d < depth; d++) {
        if (cur * dist < start) cur ++; //TODO: changed from index to start
        if (cur * dist >= n) return -1;

        if (table[d][cur] >= value) cur = PARENT(cur);
        else break;

        dist <<= 1;
    }

    for ( ; d > 0; d--) {
        if (table[d - 1][LEFT(cur)] < value) cur = LEFT(cur);
        else cur = RIGHT(cur);
    }
    return cur;
}


void ComputeANSV_Linear(long a[], long n, long leftElements[], long rightElements[], long offset) {
    long i, top;
    long *stack = new long[n];

    for (i = 0, top = -1; i < n; i++) {
        while (top > -1 && a[stack[top]] > a[i]) top--;
        if (top == -1) leftElements[i] = -1;
        else leftElements[i] = stack[top] + offset;
        stack[++top] = i;
    }

    for (i = n - 1, top = -1; i >= 0; i--) {
        while (top > -1 && a[stack[top]] > a[i]) top--;
        if (top == -1) rightElements[i] = -1;
        else rightElements[i] = stack[top] + offset;
        stack[++top] = i;
    }
    delete[] stack;
}

inline long cflog2(long i) {
    long res = 0;

    i--;
    if (i >> 16) {
        res += 16;
        i >>= 16;
    } else i &= 0xffff;

    for (; i; i >>= 1) res++;
    return res;
}

void ComputeANSV(long *a, long n, long *left, long *right, long blockSize) {
    long l2 = cflog2(n);
    long depth = l2 + 1;
    long **table = new long*[depth];

    table[0] = a;
    long m = n;
    for (long i = 1; i < depth; i++) {
        m = (m + 1) / 2;
        table[i] = new long[m];
    }

    m = n;
    for (long d = 1; d < depth; d++) {
        long m2 = m / 2;

        parlay::parallel_for(0, m2, [&] (size_t i) {
            table[d][i] = min(table[d - 1][LEFT(i)], table[d - 1][RIGHT(i)]);
        });

        if (m % 2) {
            table[d][m2] = table[d - 1][LEFT(m2)];
        }

        m = (m + 1) / 2;
    }

    parlay::blocked_for(0, n, blockSize, [&] (size_t blockNumber, size_t i, size_t j) {
        ComputeANSV_Linear(a + i, j - i, left + i, right + i, i);

        long tmp = i;
        for (long k = i; k < j; k++) {
            if (left[k] == -1) {
                if (tmp != -1 && a[tmp] >= a[k]) {
                    tmp = getLeft_opt(table, depth, n, k, tmp);
                }
                left[k] = tmp;
            }
        }

        tmp = j - 1;
        for (long k = j - 1; k >= (long)i; k--) {
            if (right[k] == -1) {
                if (tmp != -1 && a[tmp] >= a[k]) {
                    tmp = getRight_opt(table, depth, n, k, tmp);
                }
                right[k] = tmp;
            }
        }
    });

    for (long i = 1; i < depth; i++) delete table[i];
    delete[] table;
}


// Added by Rolf Svenning. Simply converts input format and calls the original function.
tuple<sequence<VI>, sequence<VI>, float> ANSV_shunZhao_orginal(sequence<long> &A_, long blockSize){
    internal::timer tVIs("TIME VIs:");
    tVIs.start();
    const long n = A_.size();
    long *L = new long[n];
    long *R = new long[n];
    long *A = new long[n];
    for(int i=0; i < n; i++){
        A[i] = A_[i];
    }
    tVIs.stop();
    internal::timer t("Time");
    t.start();
    ComputeANSV(A, n, L, R, blockSize);
    float time = t.total_time();
    tVIs.start();
    parlay::sequence<VI> L_(n);
    parlay::sequence<VI> R_(n);
    for(long i=0; i < n; i++){
        L_[i] = VI((L[i] != -1) ? A[L[i]] : -1, L[i]);
        R_[i] = VI((R[i] != -1) ? A[R[i]] : -1, R[i]);
    }
    delete [] L;
    delete [] R;
    delete [] A;
    cout << "Time VIs: " << tVIs.total_time() << endl;
    return {L_, R_, time};
}



// Print the elements of the array
//bool verbose = false;
//if (verbose) {
//std::cout << "A" << std::endl;
//for (int i : A) {
//std::cout << i << ' ';
//}
//
//std::cout << std::endl << "L" << std::endl;
//for (int i : L) {
//std::cout << i << ' ';
//}
//
//std::cout << std::endl << "R" << std::endl;
//for (int i : R) {
//std::cout << i << ' ';
//}
//}