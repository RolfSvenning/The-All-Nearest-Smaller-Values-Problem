//
// Created by Rolf Svenning on 21/11/2023.
//

#include "data.h"
#include <array>
#include <numeric>
#include "random"

parlay::sequence<long> returnSortedArray(long n){
  parlay::sequence<long> A(n);
  std::iota(A.begin(), A.end(), 1);
  return A;
}

parlay::sequence<long> returnMergeArray(long n){
    parlay::sequence<long> A(n);
  int nhalf = floor(n/2);
  for (int i = 0; i < nhalf; i++){
    A[i] = i;
  }
  for (int i = nhalf; i < n; i++){
    A[i] = n - i - 1;
  }
  return A;
}

std::tuple<long, long> returnRandomNandBlocksize(){
    // RANDOM N AND BLOCK SIZE
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> dn(2, 12345); // define the range
    long n = dn(gen);
    std::uniform_int_distribution<> db(2, std::min(40000, (int)n/2)); // define the range
    long blockSize = 2 * db(gen); //TODO: only works for even block_size
    return {n, blockSize};
}