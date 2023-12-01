#include "../ParallelMinBinaryTrees/parallelMinBinaryTreeArray.h"
#include "seq_array_n_work.h"
#include "../Glue/_aux.h"
#include "nlogn_work_shun_and_zhao.h"
#include <iostream>


long findLeftMatch(long n, const parlay::sequence<long> &T, long d, parlay::sequence<VI> &L, int i, long start) {
    long iLast = start;
    long iCurr = parent(start);
    // GOING UP THE TREE <------
    while (iCurr != 0 and (iLast == child(iCurr, 1) or T[child(iCurr, 1)] > T[i])) {
        iLast = iCurr;
        iCurr = parent(iCurr);
    }
    // LEFT MATCH EXISTS <------
    if (iLast == child(iCurr, 2) and T[child(iCurr, 1)] <= T[i]) {
        // GOING DOWN THE TREE <------
        iCurr = child(iCurr, 1);
        while (iCurr < n - 1) { //still among nodes with children
            long iRC = child(iCurr, 2);
            // right child exists and is in direction of smaller value
            if (iRC < 2 * n - 1 and T[iRC] <= T[i]) {
                iCurr = iRC;
            } else {
                // otherwise guaranteed to be in other direction
                iCurr = child(iCurr, 1);
            }
        }
        L[TtoA(i, d, n)] = VI(T[iCurr], TtoA(iCurr, d, n));
        return iCurr;
    }
    return -1;
}

long findRightMatch(long n, const parlay::sequence<long> &T, long d, parlay::sequence<VI> &R, int i, long start) {
    long iLast = start;
    long iCurr = parent(start);

    while (iCurr != 0 and (iLast == child(iCurr, 2) or T[child(iCurr, 2)] > T[i])) {
        iLast = iCurr;
        iCurr = parent(iCurr);
    }

    if (iLast == child(iCurr, 1) and T[child(iCurr, 2)] <= T[i]) {
        iCurr = child(iCurr, 2);
        while (iCurr < n - 1) {
            long iLC = child(iCurr, 1);
            if (iLC < 2 * n - 1 and T[iLC] <= T[i]) iCurr = iLC;
            else iCurr = child(iCurr, 2);
        }
        R[TtoA(i, d, n)] = VI(T[iCurr], TtoA(iCurr, d, n));
        return iCurr;
    }
    return -1;
}



void matchNonlocal(long i, long j, long n, long d, parlay::sequence<long> &A, parlay::sequence<VI> &L, parlay::sequence<VI> &R,
                        parlay::sequence<long> &T) {
    // FIND LEFT MATCHES
    long TLi = AtoT(i, d, n);
    long ALi = i;
    for (int k = i; k < j; k++){
        if (L[k].ind == -1) {
            // find new match using tree or same match as previous
            if ((TLi != -1 and A[ALi] > A[k]) or k == i){
                TLi = findLeftMatch(n, T, d, L, AtoT(k, d, n), TLi);
                ALi = TtoA(TLi, d, n);
            } else if (TLi != -1 ) L[k] = VI(A[ALi], ALi);
        }
    }

    // RIGHT MATCHES
    long TRi = AtoT(j - 1, d, n);
    long ARi = j - 1;
    for (int k = j - 1; k >= i; k--) {
        if (R[k].ind == -1) {
            // find new match using tree or same match as previous
            if ((TRi != -1 and A[ARi] > A[k]) or k == j - 1){
                TRi = findRightMatch(n, T, d, R, AtoT(k, d, n), TRi);
                ARi = TtoA(TRi, d, n);
            } else if (TRi != -1) R[k] = VI(A[ARi], ARi);
        }
    }
}

std::tuple<parlay::sequence<VI>, parlay::sequence<VI>> ANSV_nlogn_mine(parlay::sequence<long> &A, const long blockSize){
    auto [T,d] = createBinaryTreeForInput(A);
    long n = A.size();
    parlay::sequence<VI> L(n);
    parlay::sequence<VI> R(n);

    parlay::blocked_for(0, n, blockSize, [&] (size_t blockNumber, long i, long j) {
        ComputeANSV_Linear(A, j - i, L, R, i);
        matchNonlocal(i, j, n, d, A, L, R, T);
    });

    return {L, R};
}
