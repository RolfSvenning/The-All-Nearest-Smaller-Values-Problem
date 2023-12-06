#include "ANSV/nlogn_work_shun_and_zhao.h"
#include "Glue/_aux.h"
#include "Glue/data.h"
#include "Testing/TestANSV.h"
#include "iostream"
#include "limits"
#include "parlay/internal/get_time.h"
#include "parlay/primitives.h"
#include "ANSV/nlogn_work_mine.h"
#include "ANSV/berkmanOptimal.h"

int main() {
    long n = 14; // 1234567
    const long blockSize = 10; //TODO: only works for even block_size
    parlay::sequence<long> A = returnMergeArray(n);
    auto [L, R] = ANSV_Berkman(A, blockSize);
    printArray(A);
    printArraysVI(std::list<parlay::sequence<VI>>{L, R});

//    for (int i = 0; i < 100; ++i) {
//        auto [n, blockSize] = returnRandomNandBlocksize();
////        parlay::sequence<long> A = returnRandomArray(n, 100); // TODO RUN WITH DUPLICATES
//        parlay::sequence<long> A = returnMergeArray(n);
//        testArrayShunZhaoAndMine(A, blockSize);
//    }
//    for (int i = 0; i < 2000; ++i) {
//        long n = 6;
//        long blockSize = 4;
////        parlay::sequence<long> A = returnRandomArray(n, 100); // TODO RUN WITH DUPLICATES
//        parlay::sequence<long> A = returnMergeArray(n);
//        testArrayShunZhaoAndMine(A, blockSize);
//    }

    return 1;
}