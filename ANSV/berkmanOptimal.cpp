#include "berkmanOptimal.h"
#include "parlay/parallel.h"
#include "../ParallelMinBinaryTrees/parallelMinBinaryTreeArray.h"
#include "nlogn_work_shun_and_zhao.h"
#include "nlogn_work_mine.h"
#include "../Glue/_aux.h"


long findRepresentatives(parlay::sequence<long> &A, long i, long j) {
    long i1 = i;
    for (long k = i + 1; k < j; ++k) {
        if (A[k] < A[i1]) i1 = k;
    }
    return i1;
}

void farAwayBlocks_ANSV_linear(parlay::sequence<long> &A, long a, long b, long c, long d, parlay::sequence<VI> &L, parlay::sequence<VI> &R) {
    if (a == -1 or d == -1) return;

    // FIND MATCHES BY MERGING
    long i = b - 1;
    long j = c;
    while(i > a or j < d - 1) {
        if (A[i] < A[j]) {
            if (L[j].ind == -1) L[j] = VI(A[i], i);
            j++;
        }
        else {
            if (R[i].ind == -1) R[i] = VI(A[j], j);
            i--;
        }
    }
}

std::tuple<long, long> findLeftAndRightMatch(long n, const parlay::sequence<long> &T, long d, parlay::sequence<VI> &L, parlay::sequence<VI> &R, int i){
    long iL = findLeftMatch(n, T, d, L, i);
    long iR = findRightMatch(n, T, d, R, i);
    return {iL != -1 ? TtoA(iL, d, n) : -1, iR != -1 ? TtoA(iR, d, n) : -1};
}

std::tuple<parlay::sequence<VI>, parlay::sequence<VI>> ANSV_Berkman(parlay::sequence<long> &A, const long blockSize){
    // ------------ STEP 1: LOCAL MATCHES & REPRESENTATIVES ------------
    // 1) Create a min-binary tree for the input.
    // 2) For each group:
    //    a) Find local matches in each group of size 'blockSize'
    //    b) Find representative ri, that is, the (index of) smallest value in each group
    //    c) Find VIs for ri. That is, left VI(ri) = (_,b1) and right VI(ri) = (_,b2).
    //    d) Mark b1 and b2 in array Borders to be matched later.
    //
    // Notes: representatives are stored in an array REPs of size ceil(n / blockSize) [r1, r2, ...]
    // Notes: borders are stored in an array B of size 2 * ceil(n / blockSize) [(i11, i12), (i21, i22), ...]

    auto [T,d] = createBinaryTreeForInput(A);
    long n = A.size();
    long blockCount = (long)ceilf((float)n / (float)blockSize); // really?
    parlay::sequence<VI> L(n);
    parlay::sequence<VI> R(n);
    parlay::sequence<long> REPs(blockCount);
    parlay::sequence<long> B(2 * blockCount);

    parlay::blocked_for(0, n, blockSize, [&] (size_t blockNumber, long i, long j) {
        // LOCAL MATCHES
        ComputeANSV_Linear(A, j - i, L, R, i);

        // REPRESENTATIVES
        auto ri = findRepresentatives(A, i, j);
        REPs[blockNumber] = ri;

        // MARK BORDERS
        auto  [b1, b2] = findLeftAndRightMatch(n, T, d, L, R, AtoT(ri, d, n));

        B[2 * blockNumber] =  b1;
        B[2 * blockNumber + 1] = b2;

    });

    // ------------ STEP 2: NONLOCAL MATCHES OF BORDERS ------------
    parlay::parallel_for(1, B.size(), [&] (long i) {
      if (B[i] != -1) findLeftAndRightMatch(n, T, d, L, R, AtoT(B[i], d, n));
    });

    // ------------ STEP 3: NONLOCAL MATCHES BY MERGING ------------
    // 1) For each group BC:
    //    a) Find the blocks (BL, BR) matched by the representatives
    //    b) If BL is adjacent to BC, then find local matches by merging A[b1:r1] (or using a stack)
    //    c) Repeat b) for BR symmetrically
    //
    //    d) Lookup in REPs the index bBR of the left match of rBR
    //       two cases:
    //         i  ) bBR is not in BL. Then do nothing
    //         ii ) bBR is in BL (where rBL <= bBR). Find nonlocal matches in ]BL_r2, iRL[, ]iR, BR_r1[ by merging
    //    f) Repeat d) for bBL symmetrically
    //
    // Notes:
    // b1:  left match of ri of BC
    // bBL: right match of r2 of BL
    // b2:  right match of ri of BG
    // bBR: left match of r1 of BR
    // BL[.rBL....bBR.b1...] BC[...ri..] BR[...bBR.b2.rBR.]

    parlay::blocked_for(0, n, blockSize, [&] (size_t BCi, long i, long j) {
        // SETUP
        auto ri = REPs[BCi];
        auto [b1, b2] = std::tuple{B[2 * BCi], B[2 * BCi + 1]};
        auto [BLi, BRi] = std::tuple{b1 / blockSize, b2 / blockSize};
        auto [rBL, rBR] = std::tuple{REPs[BLi], REPs[BRi]};

        // ADJACENT MERGING
        if (BLi + 1 == BCi and b1 != -1) ComputeANSV_Linear(A, ri - b1 + 1, L, R, b1);
        if (BRi - 1 == BCi and b2 != -1) ComputeANSV_Linear(A, b2 - ri + 1, L, R, ri);

        // FAR-AWAY MERGING
        if (b1 == -1 or b2 == -1) return; // no far-away merging
        auto [bBL, bBR] = std::tuple{B[2 * BLi + 1], B[2 * BRi]};

        // block BL matched by both BC and BR
        if (BLi == bBR / blockSize) farAwayBlocks_ANSV_linear(A, bBR, b1 + 1, b2, rBR + 1, L, R);
        // block BR matched by both BC and BL
        if (BRi == bBL / blockSize) farAwayBlocks_ANSV_linear(A, rBL, b1 + 1, b2, bBL + 1, L, R);
    });

    return {L, R};
}