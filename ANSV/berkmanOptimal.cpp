//
// Created by Rolf Svenning on 25/10/2023.
//

#include "berkmanOptimal.h"
#include "parlay/io.h"
#include "parlay/parallel.h"
#include "../Glue/VI.h"
#include "../ParallelMinBinaryTrees/parallelMinBinaryTreeArray.h"
#include "nlogn_work_shun_and_zhao.h"
#include "nlogn_work_mine.h"
#include "../Glue/_aux.h"
#include <parlay/hash_table.h>


std::tuple<long, long> findRepresentatives(parlay::sequence<long> &A, long i, long j) {
    long i1 = i;
    long i2 = i;
    for (long k = i + 1; k < j; ++k) {
        if (A[k] < A[i1]) {
            i1 = k;
            i2 = k;
        }
        else if (A[k] == A[i1]) i2 = k;
    }
//    std::cout << "i1: " << i1 << " i2: " << i2 << std::endl;
//    std::cout << "A[i1]: " << A[i1] << " A[i2]: " << A[i2] << std::endl;
//    std::cout << to_chars(A.subseq(i, j)) << std::endl
//    TODO: remove later
    assert(i1 <= i2);
    assert(A[i1] == A[i2]);
    assert(A[i1] == parlay::min_element(A.subseq(i, j))[0]);
    return {i1, i2};
}

void farAwayBlocks_ANSV_linear(parlay::sequence<long> &A, long a, long b, long c, long d, parlay::sequence<VI> &L, parlay::sequence<VI> &R) {
    if (a == -1 or d == -1) return;
//    long a = std::max(static_cast<long>(0), static_cast<long>(a_));
//    long d = std::min(static_cast<long>(A.size()), static_cast<long>(d_));
//    printArray(A);
//    std::cout << "a, b, c, d: " << a << " " << b << " " << c << " " << d << std::endl;
//
//    std::cout << parlay::to_chars(A.subseq(a, b)) << std::endl;
//    printArrayVI(R.subseq(a, b));

//    auto Asub = A.subseq(a, b);
//    for(long i = 0; i < (long)Asub.size(); ++i) {
//        std::cout << "Ai: " << Asub[i] << " " << (R[a + i].ind == -1) << std::endl;
//    }

    // ASSERTIONS: both sequences are sorted
//    auto Aab = parlay::filter(Asub, [&] (long i) { return R[a + i].ind == -1; });
//    if (Aab.size() > 1) std::cout << "Aab: " << parlay::to_chars(Aab) << std::endl;
//    std::cout << "Aab: " << parlay::to_chars(Aab) << std::endl;

//    for(long i = 0; i < (long)Aab.size() - 1; ++i) {
//        std::cout << "i: " << i << Aab.size() - 1 << std::endl;
//        assert(Aab[i] <= Aab[i + 1]);
//    }
//    auto Acd = parlay::filter(A.subseq(c, d), [&] (long i) { return L[c + i].ind == -1; });
//    if (Acd.size() > 1) std::cout << "Acd: " << parlay::to_chars(Acd) << std::endl;
//    std::cout << "Acd: " << parlay::to_chars(Acd) << std::endl;
//    printArrayVI(L);
//    for(long i = 0; i < (long)Acd.size() - 1; ++i) {
//        assert(Acd[i] >= Acd[i + 1]);
//    }

    // FIND MATCHES BY MERGING
//    std::cout << "merging" << std::endl;
    long i = b - 1;
    long j = c;
    while(i > a or j < d - 1) { // actually i != a, no?
//        std::cout << "i, j: " << i << " " << j << std::endl;
        if (A[i] == A[j]) {
            if (L[j].ind == -1) L[j] = VI(A[i], i);
            if (R[i].ind == -1) R[i] = VI(A[j], j);
            i--;
            j++;
        }
        else if (A[i] < A[j]) {
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
    //    b) Find representatives, that is, the leftmost and rightmost smallest elements (r1, r2) in each group
    //    c) Find VIs for r1 and r2. That is, left VI(r1) = (_,i1) and right VI(r2) = (_,i2).
    //    d) Mark i1 and i2 in array Borders to be matched later.
    //
    // Notes: representatives are stored in an array REPs of size 2 * ceil(n / blockSize) [(r11,r12), (r21,r22), ...]
    // Notes: borders are stored in an array B of size 2 * ceil(n / blockSize) [(i11, i12), (i21, i22), ...]

    auto [T,d] = createBinaryTreeForInput(A);
    long n = A.size();
    long blockCount = 2 * (long)ceilf((float)n / (float)blockSize); // really?
    parlay::sequence<VI> L(n);
    parlay::sequence<VI> R(n);
    parlay::sequence<long> REPs(blockCount);
    parlay::sequence<long> B(blockCount);

    parlay::blocked_for(0, n, blockSize, [&] (size_t blockNumber, long i, long j) {
        // LOCAL MATCHES
        ComputeANSV_Linear(A, j - i, L, R, i);

        // REPRESENTATIVES
        auto [r1, r2] = findRepresentatives(A, i, j);
        REPs[2 * blockNumber] = r1;
        REPs[2 * blockNumber + 1] = r2;

        // MARK BORDERS
        // /TODO: Refactor to just finding the relevant one?
        auto  [b1, unused1] = findLeftAndRightMatch(n, T, d, L, R, AtoT(r1, d, n));
        auto  [unused2, b2] = findLeftAndRightMatch(n, T, d, L, R, AtoT(r2, d, n));
//        std::cout << "blockNumber: " << blockNumber << " r1: " << r1 << " r2: " << r2 << std::endl;
        B[2 * blockNumber] =  b1;
        B[2 * blockNumber + 1] = b2;

    });

    // ------------ STEP 2: NONLOCAL MATCHES OF BORDERS ------------
    // Note: Multiple representatives may match the same border, so we remove duplicates
    auto Bdistincts = parlay::remove_duplicates_ordered(B);
    // TODO: return sorted sequence or not?
    // TODO: %https://cmuparlay.github.io/parlaylib/algorithms/primitives.html#remove-duplicates
//    std::cout << "B, Bdistincts: " << std::endl;
//    printArray(B);
//    printArray(Bdistincts);

    // TODO: start at 1 only if ordered
    parlay::parallel_for(1, Bdistincts.size(), [&] (long i) {
        findLeftAndRightMatch(n, T, d, L, R, AtoT(Bdistincts[i], d, n));
    });

    // ------------ STEP 3: NONLOCAL MATCHES BY MERGING ------------
    // 1) For each group BC:
    //    a) Find the blocks (BL, BR) matched by the representatives
    //    b) If BL is adjacent to BC, then find local matches by merging A[b1:r1] (or using a stack)
    //    c) Repeat b) for BR symmetrically
    //
    //    d) Lookup in REPs the index iRL of the left match of the left representative in BR
    //    e) Three cases:
    //       i  ) iRL is not in BL. Then do nothing
    //       ii ) iRL is in BL and BL_r2 <= iRL. Find nonlocal matches in ]BL_r2, iRL[, ]iR, BR_r1[ by merging
    //    f) Repeat d/e) for iLR symmetrically
    //    g) Assert BL and BR both "match each other" iff their representatives match have same value
    //
    // Notes:
    // b1:  left match of r1 of BC
    // iLR: right match of r2 of BL
    // b2:  right match of r2 of BG
    // iRL: left match of r1 of BR
    // BL[.r1...r2.iRL.iL...] BG[...r1....r2..] BR[...iR.iLR.r1...r2.]

    parlay::blocked_for(0, n, blockSize, [&] (size_t BCi, long i, long j) {
        // SETUP
        auto [r1, r2] = std::tuple{REPs[2 * BCi], REPs[2 * BCi + 1]};
        auto [b1, b2] = std::tuple{B[2 * BCi], B[2 * BCi + 1]};
//        std::cout << "BCi: " << BCi << " r1: " << r1 << " r2: " << r2 << " b1: " << b1 <<" b2: " << b2 << std::endl;
        auto [BLi, BRi] = std::tuple{b1 / blockSize, b2 / blockSize};
//        std::cout << "BCi: " << BCi << " BLi: " << BLi << " BRi: " << BRi << std::endl;
        auto [rBL, rBR] = std::tuple{REPs[2 * BLi + 1], REPs[2 * BRi]};

        // ADJACENT MERGING
        if (BLi + 1 == BCi and b1 != -1) ComputeANSV_Linear(A, r1 - b1 + 1, L, R, b1);
        if (BRi - 1 == BCi and b2 != -1) ComputeANSV_Linear(A, b2 - r1 + 1, L, R, r1);

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

//parlay::sequence<long> hardcodedInputOfLength16(){
//    // { 0  1  2  3  --  4  5  6  7  --   8  9 10 11  --  12 13 14 15}
//    // {15  0  8  3  -- 11 12 14 13  --  10  9  6  8  --   7  2  1  4} # merging for example 0 8 3 with 2 1 (split by 6)
//    return parlay::sequence<long>{15, 0, 8, 3, 11, 12, 14, 13, 10, 9, 6, 8, 7, 2, 1, 4};
//}
//
//parlay::sequence<long> getInput(int dataType){
//    if (dataType == 0) return hardcodedInputOfLength16();
//    else assert(0 == 1);
//}


//int main(int argc, char* argv[]) {
    // ------------ SETUP ------------
//    if (argc != 3){
//        std::cout << "Usage: missing 'n' or 'dataType' argument." << std::endl;
//        return 0;
//    }
//
//    long n;
//
//    int dataType;
//    try { dataType = std::stol(argv[2]); }
//    catch (...) { std::cout << "parameter dataType malformed (should be small integer)" << std::endl; return 1; }
//    assert (dataType >= 0 and dataType <= 5);
//    std::cout << "n and dataType: " << n << " " << dataType << std::endl;
//
//    // ------------ INPUT ------------
//    parlay::sequence<long> A = getInput(dataType);
//    std::cout << "A: " << parlay::to_chars(A) << std::endl;
//
//    // ------------ STEP 1: GROUPS ------------
//    // divides input into groups of size log(n) and finds local matches
//    // and smallest element in group for the min-binary tree.
//    long s = ceil(log2(n));
//    long Gn = ceil(n / s);


//    return 7;
//}