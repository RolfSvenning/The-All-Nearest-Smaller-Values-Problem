
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

void printArrayNormal(long *A_, long n) {
    parlay::sequence<long> A = parlay::tabulate(n, [&] (long i) {
        return A_[i];
    });
    printArray(A);
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