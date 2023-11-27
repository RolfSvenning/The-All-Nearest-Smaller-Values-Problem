
#include "_aux.h"
#include "algorithm"
#include "iostream"
#include "parlay/io.h"
#include "random"
#include <array>
#include <list>
#include <utility>

void printParlayArrayVI(parlay::sequence<VI> A, std::string s){
  std::cout << s << parlay::to_chars(parlay::map(A, [&] (VI vi) {return vi.ind;})) << std::endl;
}

bool isPowerOfTwo(long x){
  return (x>0 && ((x & (x-1)) == 0));
}

void printArrayVI(parlay::sequence<VI> A) {
    for (VI a : A)
        std::cout << "(" << a.v << ", " << a.ind << ")";
    std::cout << std::endl;
}

void printArraysVI(const std::list<parlay::sequence<VI>>& AS) {
    for (parlay::sequence<VI> A : AS) {
        printArrayVI(A);
    }
}

void printArray(parlay::sequence<long> A) {
        std::cout << to_chars(A)  << std::endl;
}

// Returns an array containing a random permutation of [0...n-1]
parlay::sequence<long> returnRandomArray(long n) {
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

//std::tuple<std::array<VI, n>, std::array<VI, n>> seqToArray(std::tuple<parlay::sequence<VI>, parlay::sequence<VI>> LR){
//    auto [L, R] = std::move(LR);
//    std::array<VI, n> L_;
//    std::array<VI, n> R_;
//    for(int i=0; i < n; i++){
//        L_[i] = L[i];
//        R_[i] = R[i];
//    }
//    return {L_, R_};
//}