#include "../ParallelMinBinaryTrees/parallelMinBinaryTreeArray.h"
#include "parlay/primitives.h"
#include "seq_array_n_work.h"
#include "../Glue/_aux.h"
#include <iostream>

void findLeftMatch(long n, const parlay::sequence<long> &T, long d, parlay::sequence<VI> &L, int i) {
    long iLast = i;
    long iCurr = parent(i);
    // GOING UP THE TREE <------
    while (iCurr != 0 and (iLast == child(iCurr, 1) or T[child(iCurr, 1)] > T[i])) {
        iLast = iCurr;
        iCurr = parent(iCurr);
    }
    // NO LEFT MATCH <------
    if (iLast == child(iCurr, 1) or T[child(iCurr, 1)] > T[i]) {
        assert (iCurr == 0);
    } else {
        // GOING DOWN THE TREE <------
        iCurr = child(iCurr, 1);
        while (iCurr < n - 1) { //still among nodes with children
            long iRC = child(iCurr, 2);
            // right child exists and is in direction of smaller value
            if (iRC < 2 * n - 1 and T[iRC] <= T[i]) {
                iCurr = iRC;
            } else {
                // otherwise guaranteed to be in other direction
                iCurr = child(iCurr, 1);
            }
        }
        L[treeIndexToArrayIndex(i, d, n)] = VI(T[iCurr], treeIndexToArrayIndex(iCurr, d, n));
    }
}

void findRightMatch(long n, const parlay::sequence<long> &A, parlay::sequence<long> &L, int i) {
    // TODO: make this
}

std::tuple<parlay::sequence<VI>, parlay::sequence<VI>> ANSV_nlogn_mine(parlay::sequence<long> A){
    auto [T,d] = createBinaryTreeForInput(A);
    long n = A.size();
    parlay::sequence<VI> L(n);
    parlay::sequence<VI> R(n);
    parlay::parallel_for (
        n - 1, 2 * n - 1,
        [&] (size_t i ){ findLeftMatch(n, T, d, L, i);}
        );
    return {L, R};
}

int main2(int argc, char* argv[]){
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
    parlay::internal::timer t("Time ");

    // CREATING MIN BINARY TREE FOR RANDOM INPUT OF SIZE n
    parlay::sequence<long> A = {9, 5, 2, 4, 6, 5};
    assert(A.size() == n);


    t.start();
    auto [T,d] = createBinaryTreeForInput(A);
    t.next("min binary tree");;

    parlay::sequence<VI> L(n);
//     --- PARALLEL --- FINDING ALL LEFT MATCHES USING THE TREE
    parlay::parallel_for (n - 1, 2 * n - 1, [&] (size_t i ){ findLeftMatch(n, T, d, L, i);
    });
    t.next("parallel: ");
    printParlayArrayVI(L, "L: ");
    return 1;
}