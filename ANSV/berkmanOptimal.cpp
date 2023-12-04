//
// Created by Rolf Svenning on 25/10/2023.
//

#include "berkmanOptimal.h"
#include "parlay/io.h"
#include "parlay/parallel.h"
#include "../Glue/VI.h"
#include "../ParallelMinBinaryTrees/parallelMinBinaryTreeArray.h"
#include "nlogn_work_shun_and_zhao.h"

parlay::sequence<long> hardcodedInputOfLength16(){
  // { 0  1  2  3  --  4  5  6  7  --   8  9 10 11  --  12 13 14 15}
  // {15  0  8  3  -- 11 12 14 13  --  10  9  6  8  --   7  2  1  4} # merging for example 0 8 3 with 2 1 (split by 6)
  return parlay::sequence<long>{15, 0, 8, 3, 11, 12, 14, 13, 10, 9, 6, 8, 7, 2, 1, 4};
}

parlay::sequence<long> getInput(int dataType){
  if (dataType == 0) return hardcodedInputOfLength16();
  else assert(0 == 1);
}


std::tuple<parlay::sequence<VI>, parlay::sequence<VI>> ANSV_Berkman(parlay::sequence<long> &A, const long blockSize){
    // ------------ STEP 1: LOCAL MATCHES & REPRESENTATIVES ------------
    // 1) Create a min-binary tree for the input.
    // 2) For each group:
    //    a) Find local matches in each group of size 'blockSize'
    //    b) Find representatives, that is, the leftmost and rightmost smallest elements (r1,r2) in each group
    //    c) Find VIs for r1 and r2. That is, left VI(r1) = (_,i1) and right VI(r2) = (_,i2)
    //    d) Find the right VI for A[i1] and the left VI for A[i2]. (Note both are unmatched in their groups!)
    //
    // Notes: Representatives are stored in an array REPs of size 2 * ceil(n / blockSize) [(r11,r12), (r21,r22), ...]

    auto [T,d] = createBinaryTreeForInput(A);
    long n = A.size();
    parlay::sequence<VI> L(n);
    parlay::sequence<VI> R(n);

    parlay::blocked_for(0, n, blockSize, [&] (size_t blockNumber, long i, long j) {
        ComputeANSV_Linear(A, j - i, L, R, i);
        // matchNonlocal(i, j, n, d, A, L, R, T);
    });

    // ------------ STEP 2: NONLOCAL MATCHES BY MERGING ------------
    // 1) For each group BG:
    //    a) Find the blocks (BL, BR) matched by the representatives
    //    b) Lookup in REPs the index iRL of the left match of the left representative in BR
    //    c) Three cases:
    //       i  ) iRL is not in BL. Then do nothing
    //       ii ) iRL is in BL and BL_r2 <= iRL. Find nonlocal matches in ]BL_r2, iRL[, ]iR, BR_r1[ by merging
    //    d) Repeat c) for iLR symmetrically
    //    e) Assert BL and BR both "match each other" iff their representatives match have same value
    //    f) If BL and BG are adjacent, then find local matches by merging A[iL:r1] (or using a stack)
    //    d) Repeat f) for BR symmetrically
    //
    // Notes:
    // iL:  left match of r1 of BG
    // iLR: right match of r2 of BL
    // iR:  right match of r2 of BG
    // iRL: left match of r1 of BR
    // BL[.r1...r2.iRL.iL...] BG[...r1....r2..] BR[...iR.iLR.r1...r2.]

    return {L, R};
}

int main(int argc, char* argv[]) {
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


    return 7;
}