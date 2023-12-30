#include "berkmanOptimal.h"
#include "parlay/parallel.h"
#include "parlay/primitives.h"
//#include "../ParallelMinBinaryTrees/parallelMinBinaryTreeArray.h"
#include "nlogn_work_shun_and_zhao.h"
#include "shunZhaoOriginal.h"
#include "../Glue/_aux.h"

using namespace std;
using namespace parlay;

long findRepresentative(long *A, long i, long j) {
    long i1 = i;
    for (long k = i + 1; k < j; ++k) {
        if (A[k] < A[i1]) i1 = k;
    }
    return i1;
}

void farAwayBlocks_ANSV_linear(long *A, long a, long b, long c, long d, long *L, long *R) {
    if (a == -1 or d == -1) return;

    // FIND MATCHES BY MERGING
    long i = b - 1;
    long j = c;
    while(i > a or j < d - 1) {
        if (A[i] < A[j]) {
            if (L[j] == -1) L[j] = i;
            j++;
        }
        else {
            if (R[i] == -1) R[i] = j;
            i--;
        }
    }
}

tuple<long, long> findLeftAndRightMatch(long n, long **T, long d, long *L, long *R, int i){
    long iL = getLeft_opt( T, d, n, i, i);
    long iR = getRight_opt(T, d, n, i, i);
    L[i] = iL;
    R[i] = iR;
    return {iL, iR};
//    return {iL != -1 ? TtoA(iL, d, n) : -1, iR != -1 ? TtoA(iR, d, n) : -1};
}

//void adjacentMergeLeft(long A[], long n, long L[], long offset) {
//    long i, top;
//    long *stack = new long[n];
//
//    for (i = 0, top = -1; i < n; i++) {
//        while (top > -1 && A[stack[top] + offset] > A[i + offset]) top--;
//        if (top != -1) {
//            cout << "i, top, stack[top], offset " << i << " " << top << " " << stack[top] << " " << offset << endl;
//            L[i] = stack[top] + offset;
//        }
//        stack[++top] = i;
//    }
//
//    delete[] stack;
//}
//
//void adjacentMergeRight(long A[], long n, long R[], long offset) {
//    long i, top;
//    long *stack = new long[n];
//
//    for (i = n - 1, top = -1; i >= 0; i--) {
//        while (top > -1 && A[stack[top] + offset] > A[i + offset]) top--;
//        if (top != -1) R[i] = stack[top] + offset;
//        stack[++top] = i;
//    }
//    delete[] stack;
//}

void adjacentMergeBOTH(long *A, long n, long *L, long *R, long offset) {
    long i, top;
    long *stack = new long[n];

    for (i = offset, top = -1; i < n + offset; i++) {
        while (top > -1 && A[stack[top]] > A[i]) top--;
        if (top != -1) L[i] = stack[top];
        stack[++top] = i;
    }

    for (i = n - 1 + offset, top = -1; i >= offset; i--) {
        while (top > -1 && A[stack[top]] > A[i]) top--;
        if (top != -1) R[i] = stack[top];
        stack[++top] = i;
    }
    delete[] stack;
}


//tuple<sequence<long>, sequence<long>, float> ANSV_Berkman(sequence<long> &A, const long blockSize){
double ANSV_Berkman(long *A, long n, long *L, long *R, long blockSize){
//    long n = A.size();
//    sequence<long> L(n, -1);
//    sequence<long> R(n, -1);
    internal::timer t("BERKMAN");
    t.start();

    // ------------ STEP 1: LOCAL MATCHES & REPRESENTATIVES ------------
    // 1) Create a min-binary tree for the input.
    // 2) For each group:
    //    a) Find local matches in each group of size 'blockSize'
    //    b) Find representative ri, that is, the (index of) smallest value in each group
    //    c) Find matches of ri. That is, left match b1 and right match b2.
    //    d) Mark borders b1 and b2 in B to be matched later.
    //
    // Notes: representatives are stored in an array REPs of size ceil(n / blockSize) [r1, r2, ...]
    // Notes: borders are stored in an array B of size 2 * ceil(n / blockSize) [(i11, i12), (i21, i22), ...]

    long blockCount = (long)ceilf((float)n / (float)blockSize); // really?
    sequence<long> REPs(blockCount);
    sequence<long> B(2 * blockCount);
    t.next("BERKMAN: STEP -1");

    auto [T,d] = createBinaryTree(A, n);
    t.next("BERKMAN: STEP 0");

    blocked_for(0, n, blockSize, [&] (size_t blockNumber, long i, long j) {
        // LOCAL MATCHES

        ComputeANSV_Linear(A + i, j - i, L + i, R + i, i);

        // REPRESENTATIVES
        auto ri = findRepresentative(A, i, j);
        REPs[blockNumber] = ri;

        // MARK BORDERS
        auto  [b1, b2] = findLeftAndRightMatch(n, T, d, L, R, ri);
        B[2 * blockNumber] =  b1;
        B[2 * blockNumber + 1] = b2;
    });
    t.next("BERKMAN: STEP 1");
//    printArrayNormal(L, n);

    //TODO: review this step review this step review this step review this step
    // ------------ STEP 2: NONLOCAL MATCHES OF BORDERS ------------ //TODO: review this step review this step
    parallel_for(1, B.size(), [&] (long i) {
      if (B[i] != -1) findLeftAndRightMatch(n, T, d, L, R, B[i]);
    });
    t.next("BERKMAN: STEP 2");
//    printArrayNormal(L, n);
    // ------------ STEP 3: NONLOCAL MATCHES BY MERGING ------------
    // 1) For each group BC:
    //    a) Find the blocks (BL, BR) matched by the representatives
    //    b) If BL is adjacent to BC, then find local matches by merging A[b1:r1] (or using a stack)
    //    c) Repeat b) for BR symmetrically
    //    d) Lookup in REPs the index bBR of the left match of rBR
    //       two cases:
    //         i  ) bBR is not in BL. Then do nothing
    //         ii ) bBR is in BL (where rBL <= bBR). Find nonlocal matches in ]BL_r2, iRL[, ]iR, BR_r1[ by merging
    //    f) Repeat d) for bBL symmetrically
    //
    // Notes:
    // b1:  left match of ri of BC
    // bBL: right match of rBL
    // b2:  right match of ri of BG
    // bBR: left match of rBR
    // BL[.rBL....bBR.b1...] BC[...ri..] BR[...bBR.b2.rBR.]

    blocked_for(0, n, blockSize, [&] (size_t BCi, long i, long j) {
        // SETUP
        auto ri = REPs[BCi];
        auto [b1, b2] = tuple{B[2 * BCi], B[2 * BCi + 1]};
        auto [BLi, BRi] = tuple{b1 / blockSize, b2 / blockSize};
        auto [rBL, rBR] = tuple{REPs[BLi], REPs[BRi]};

        // ADJACENT MERGING
//        printArrayNormal(L, n);
        if (BLi + 1 == BCi and b1 != -1) adjacentMergeBOTH(A, ri - b1 + 1, L, R, b1);
//        printArrayNormal(L, n);
        if (BRi - 1 == BCi and b2 != -1) adjacentMergeBOTH(A, b2 - ri + 1, L, R, ri);
//        printArrayNormal(L, n);
        // FAR-AWAY MERGING
        if (b1 == -1 or b2 == -1) {
//            cout << "NO far-away merging BCi " << BCi << " ri, bi: " << ri << " " << b1 << endl;
            return;
        } // no far-away merging
//        cout << "FAR-away merging b1, b2 " << b1 << " " << b2 << " BCi "<< BCi << endl;
//        printArrayNormal(L, n);
        auto [bBL, bBR] = tuple{B[2 * BLi + 1], B[2 * BRi]};

        // block BL matched by both BC and BR
        if (BLi == bBR / blockSize) farAwayBlocks_ANSV_linear(A, bBR, b1 + 1, b2, rBR + 1, L, R);
        // block BR matched by both BC and BL
        if (BRi == bBL / blockSize) farAwayBlocks_ANSV_linear(A, rBL, b1 + 1, b2, bBL + 1, L, R);
    });
    t.next("BERKMAN: STEP 3");
    return t.total_time();
}