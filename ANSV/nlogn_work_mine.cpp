#include "../ParallelMinBinaryTrees/parallelMinBinaryTreeArray.h"
#include "parlay/primitives.h"
#include "seq_array_n_work.h"
#include "../Glue/_aux.h"
#include <iostream>

void findLeftMatch(long n, const parlay::sequence<long> &T, long d, parlay::sequence<VI> &L, int i) {
    int c = -1;
    if (i == c) std::cout << "----- i: " << i << std::endl;
    long iLast = i;
    long iCurr = parent(i);
    // GOING UP THE TREE <------
    while (iCurr != 0 and (iLast == child(iCurr, 1) or T[child(iCurr, 1)] > T[i])) {
      if (i == c) std::cout << "iCurr: " << iCurr << std::endl;
        iLast = iCurr;
        iCurr = parent(iCurr);
    }
    if (i == c) std::cout << "iCurr: " << iCurr << std::endl;
    if (i == c) std::cout << "finished up" << std::endl;
    // NO LEFT MATCH <------
    if (iLast == child(iCurr, 1) or T[child(iCurr, 1)] > T[i]) {
        assert (iCurr == 0);
        if (i == c) std::cout << "no left match" << std::endl;
        if (i==c) std::cout << "treeIndexToArrayIndex: " << treeIndexToArrayIndex(i, d) << std::endl;
        if (i==c) printParlayArrayVI(L, "L before: ");
//        std::cout << "no match for i: " << i << std::endl;
//        L[treeIndexToArrayIndex(i, d)] = -1;
    } else {
        // GOING DOWN THE TREE <------
        iCurr = child(iCurr, 1);
        while (iCurr < n - 1) { //still among nodes with children
          if (i == c) std::cout << "iCurr: " << iCurr << std::endl;
            long iRC = child(iCurr, 2);
            // right child exists and is in direction of smaller value
            if (iRC < 2 * n - 1 and T[iRC] < T[i]) {
                iCurr = iRC;
            } else {
                // otherwise guaranteed to be in other direction
                iCurr = child(iCurr, 1);
            }
        }
        if (i == c) std::cout << "iCurr: " << iCurr << std::endl;
        if (i == c) std :: cout << "match is: " << T[iCurr] << std::endl;
//        assert(1 == 0); //TODO: fix here since last level not full
        if (i==c) std::cout << "i d: " << i << " " << d << std::endl;
        if (i==c) std::cout << "treeIndexToArrayIndex: " << treeIndexToArrayIndex(i, d) << std::endl;
        if (i==c) printParlayArrayVI(L, "L before: ");
//        std::cout << "match for i: " << i << std::endl;
        L[treeIndexToArrayIndex(i, d)] = VI(T[iCurr], treeIndexToArrayIndex(iCurr, d));
    }
    if (i==c) printParlayArrayVI(L, "L after: ");
}

void findRightMatch(long n, const parlay::sequence<long> &A, parlay::sequence<long> &L, int i) {
    // TODO: make this
}

std::tuple<std::array<VI, n>, std::array<VI, n>> ANSV_nlogn_mine(parlay::sequence<long> A){
    auto [T,d] = createBinaryTreeForInput(A);
    parlay::sequence<VI> L(n);
    parlay::sequence<VI> R(n);
    parlay::parallel_for (
        n - 1, 2 * n - 1,
        [&] (size_t i ){ findLeftMatch(n, T, d, L, i);}
        );
    std::array<VI, n> L_;
    std::array<VI, n> R_;
    for(int i=0; i < n; i++){
        L_[i] = L[i];
        R_[i] = R[i];
    }
    return {L_, R_};
}

int main(int argc, char* argv[]){
    // SETUP
    auto usage = "Usage: missing 'n' argument. "
                 "Creating parallel min binary tree of n elements <n>";
    if (argc != 2){
        std::cout << usage << std::endl;
        return 0;
    }

    long n;
    try { n = std::stol(argv[1]); }
    catch (...) { std::cout << usage << std::endl; return 1; }
    // for simplicity; this guarantees the input will be stored in its original order at the leaves
//    assert (pow(2,floor(log2(n))) == n);
    parlay::internal::timer t("Time ");

    // CREATING MIN BINARY TREE FOR RANDOM INPUT OF SIZE n
//    parlay::sequence<long> A = {15, 0, 8, 3, 11, 12, 14, 13, 10, 9, 6, 8, 7, 2, 1, 4};
    parlay::sequence<long> A = {9, 5, 2, 4, 6, 5};
    assert(A.size() == n);


    t.start();
    auto [T,d] = createBinaryTreeForInput(A);
    t.next("min binary tree");;

    // --- SEQUENTIAL --- FINDING ALL LEFT MATCHES USING THE TREE
    parlay::sequence<VI> L(n);
//    for (int i = n - 1; i < 2 * n - 1;){
//        findLeftMatch(n, T, L, i);
//        i = i + 1;
//    }
//    t.next("sequential: ");
//     --- PARALLEL --- FINDING ALL LEFT MATCHES USING THE TREE
    parlay::parallel_for (n - 1, 2 * n - 1, [&] (size_t i ){ findLeftMatch(n, T, d, L, i);
    });
    t.next("parallel: ");
//    std::cout << "T: " << parlay::to_chars(T) << std::endl;
    printParlayArrayVI(L, "L: ");
    return 1;
}