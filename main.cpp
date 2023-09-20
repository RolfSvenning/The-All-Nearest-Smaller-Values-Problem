#include <iostream>


//
// Created by Rolf on 9/20/2023.
//


#include "parlaylib/include/parlay/parallel.h"
#include "parlaylib/include/parlay/primitives.h"
#include "parlaylib/include/parlay/sequence.h"

parlay::sequence<long> prime_sieve(long n) {
    if (n < 2) return {};
    else {
        long sqrt = std::sqrt(n);
        auto primes_sqrt = prime_sieve(sqrt);
        parlay::sequence<bool> flags(n+1, true);  // flags to mark the primes
        flags[0] = flags[1] = false;              // 0 and 1 are not prime
        parlay::parallel_for(0, primes_sqrt.size(), [&] (size_t i) {
            long prime = primes_sqrt[i];
            parlay::parallel_for(2, n/prime + 1, [&] (size_t j) {
                flags[prime * j] = false;
            });
        }, 1);
        return parlay::filter(parlay::iota<long>(n+1),
                              [&](size_t i) { return flags[i]; });
    }
}

int test(long n) {
    parlay::sequence<int> A = parlay::sequence<int>(n);
    // parlay::parallel_for(0, primes_sqrt.size(), [&] (size_t i) {
    parlay::parallel_for(0, n - 1, [&] (int i){
        A[i] = i;
    });
    return A[5];
}

int main() {
    int n = 100;
    int res = test(n);
    std::cout << res;

    parlay::sequence<long> res2 = prime_sieve(n);
    std::cout << "   ";
    for(int i : res2){
        std::cout << i;
        std::cout << " ";
    }
    return 0;
}
