//
// Created by Rolf Svenning on 21/11/2023.
//

#include "data.h"
#include <array>
#include <numeric>
#include "random"
#include "parlay/primitives.h"

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

// Returns an array containing a random permutation of [0...n-1]
parlay::sequence<long> returnDistinctRandomArray(long n) {
    parlay::sequence<long> A = parlay::tabulate(n, [&](size_t i) { return (long)i; });

    // Shuffle the array by swapping with previous element with probability 1/(n-1)
    std::random_device rd;
    std::mt19937 gen(rd());
    for (int i = 1; i < n; ++i) {
        std::uniform_real_distribution<> dis(0.0, 1.0);
        if (dis(gen) > 1.0 / (i - 1)) {
            // Seed the random number generator
            std::random_device rd2;
            std::mt19937 gen2(rd2());
            // Define the uniform distribution
            std::uniform_int_distribution<int> dist2(0, i - 1);

            // Generate a random integer from 0 to i - 1 (inclusive)
            int randomNum = dist2(gen2);

            std::swap(A[i], A[randomNum]);
        }
    }
    return A;
}

parlay::sequence<long> returnRandomArray(long n, long maxInt=100) {
    std::random_device rd1;
    std::mt19937 gen1(rd1());
    std::uniform_int_distribution<long> dis1(0, 10000);

    parlay::random_generator gen(dis1(gen1));
    std::uniform_int_distribution<long> dis(0, maxInt);
    return parlay::tabulate(n, [&](size_t i) {
        auto r = gen[i];
        return dis(r);
    });
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