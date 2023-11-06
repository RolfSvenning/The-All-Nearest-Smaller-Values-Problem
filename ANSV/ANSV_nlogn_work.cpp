#include "../ParallelMinBinaryTrees/parallelMinBinaryTreeArray.h"
#include "parlay/primitives.h"
#include "parlay/sequence.h"
#include <iostream>
#include "parlay/io.h"

void findLeftMatch(long n, const parlay::sequence<long> &A, parlay::sequence<long> &L, int i) {
//    std::cout << "----- i: " << i << std::endl;
    long iLast = i;
    long iCurr = parent(i);
    // GOING UP THE TREE <------
    while (iCurr != 0 and (iLast == child(iCurr, 1) or A[child(iCurr, 1)] > A[i])) {
//        std::cout << "iCurr: " << iCurr << std::endl;
        iLast = iCurr;
        iCurr = parent(iCurr);
    }
//    std::cout << "iCurr: " << iCurr << std::endl;
//    std::cout << "finished up" << std::endl;
    // NO LEFT MATCH <------
    if (iLast == child(iCurr, 1) or A[child(iCurr, 1)] > A[i]) {
        assert (iCurr == 0);
//        std::cout << "no left match" << std::endl;
        L[i - n + 1] = -1;
    } else {
        // GOING DOWN THE TREE <------
        iCurr = child(iCurr, 1);
        while (iCurr < n - 1) { //still among nodes with children
//            std::cout << "iCurr: " << iCurr << std::endl;
            long iRC = child(iCurr, 2);
            // right child exists and is in direction of smaller value
            if (iRC < 2 * n - 1 and A[iRC] < A[i]) {
                iCurr = iRC;
            } else {
                // otherwise guaranteed to be in other direction
                iCurr = child(iCurr, 1);
            }
        }
//        std::cout << "iCurr: " << iCurr << std::endl;
//        std :: cout << "match is: " << A[iCurr] << std::endl;
//        assert(1 == 0); //TODO: fix here since last level not full
        L[i - n + 1] = A[iCurr];
    }
}

void findRightMatch(long n, const parlay::sequence<long> &A, parlay::sequence<long> &L, int i) {
    // TODO: make this
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
//    parlay::sequence<long> A_ = {15, 0, 8, 3, 11, 12, 14, 13, 10, 9, 6, 8, 7, 2, 1, 4};
    parlay::sequence<long> A_ = {15, 0, 8};
    assert(A_.size() == n);
    parlay::sequence<long> A = createBinaryTreeForInput(A_);
    t.start();
    std::cout << "A before fixing: " << parlay::to_chars(A) << std::endl;
    fixNode(0, A, n);
    std::cout << "A after fixing: " << parlay::to_chars(A) << std::endl;
    t.next("min binary tree");;

    // --- SEQUENTIAL --- FINDING ALL LEFT MATCHES USING THE TREE
    parlay::sequence<long> L (n);
    for (int i = n - 1; i < 2 * n - 1;){
        findLeftMatch(n, A, L, i);
        i = i + 1;
    }
    t.next("sequential: ");
    // --- PARALLEL --- FINDING ALL LEFT MATCHES USING THE TREE
    parlay::parallel_for (n - 1, 2 * n, [&] (size_t i ){ findLeftMatch(n, A, L, i);
    });
    t.next("parallel: ");
    std::cout << "A: " << parlay::to_chars(A) << std::endl;
    std::cout << "L " << parlay::to_chars(L) << std::endl;
}