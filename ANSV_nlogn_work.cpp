#include "parlay/primitives.h"
#include "parlay/sequence.h"
#include "parlay/io.h"
#include <iostream>
#include "parallelMinBinaryTreeArray.h"

// ------------- parallelMinBinaryTreeArray COPIED -------------

//parlay::sequence<long> generate_values(long n) {
//    parlay::random_generator gen;
//    std::uniform_int_distribution<long> dis(0, n-1);
//
//    return parlay::tabulate(2 * n - 1, [&] (long i) {
//        if (i <= n - 2) return -1L;
//        auto r = gen[i];
//        return dis(r);
//    });
//}
//
//long parent(long i){
//    return (i - 1) / 2;
//}
//
//long child(long i, long c){
//    assert (1 <= c and c <=2);
//    return 2 * i + c;
//}
//
//void fixNode(int i, parlay::sequence<long>& A, long n){
//    if (i > n - 2) return;
//// PARALLEL
//    if (parallel){
//        parlay::par_do_if(i < n / 1024, // i < 512
//                          [&]() {fixNode(child(i, 1), A, n);},
//                          [&]() {fixNode(child(i, 2), A, n);}
//        );
//    } else {
//        //  SEQUENTIAL
//        fixNode(child(i, 1), A, n);
//        fixNode(child(i, 2), A, n);
//    }
//    A[i] = std::min(A[child(i, 1)], A[child(i, 2)]);
//}

// ------------- parallelMinBinaryTreeArray COPIED -------------

void getSequence(long n, const parlay::sequence<long> &A, parlay::sequence<long> &L, int i) {
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
        L[i - n + 1] = A[iCurr];
    }
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
    assert (pow(2,floor(log2(n))) == n);
    parlay::internal::timer t("Time ");

    // CREATING MIN BINARY TREE ON RANDOM INPUT
    parlay::sequence<long> A = generate_values(n);
    t.start();
    fixNode(0, A, n);
    t.next("min binary tree");;

    // --- SEQUENTIAL --- FINDING ALL LEFT MATCHES USING THE TREE
    parlay::sequence<long> L (n);
    for (int i = n - 1; i < 2 * n - 1;){
        getSequence(n, A, L, i);
        i = i + 1;
    }
    t.next("sequential: ");
    // --- PARALLEL --- FINDING ALL LEFT MATCHES USING THE TREE
    parlay::parallel_for (n - 1, 2 * n, [&] (size_t i ){
        getSequence(n, A, L, i);
    });
    t.next("parallel: ");
    std::cout << "A: " << parlay::to_chars(A) << std::endl;
    std::cout << "L " << parlay::to_chars(L) << std::endl;
}