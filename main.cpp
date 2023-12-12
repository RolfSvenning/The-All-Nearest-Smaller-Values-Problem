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
//    long n = 10; // 1234567
//    const long blockSize = 4; //TODO: only works for even block_size
//    parlay::sequence<long> A = {1,1,7,8,5,4,2};
//    auto [L, R] = ANSV_Berkman(A, blockSize);
//    printArray(A);
//    printArraysVI(std::list<parlay::sequence<VI>>{L, R});

    for (int i = 0; i < 1000; ++i) {
        auto [n, blockSize] = returnRandomNandBlocksize(80000, 100);
        parlay::sequence<long> A = returnDistinctRandomArray(n);
//        parlay::sequence<long> A = returnMergeArray(n);
        testArrayShunZhaoAndMineAndBerkman(A, blockSize);
    }
    for (int i = 0; i < 100000; ++i) {
        auto [n, blockSize] = returnRandomNandBlocksize(100, 100);
//        long n = 39;
//        long blockSize = 400;
        // TODO: duplicate values actually hard to fix
        parlay::sequence<long> A = returnDistinctRandomArray(n);
        // TRY BELOW INPUT
//        parlay::sequence<long> A = {1, 7, 8, 7, 1, 6, 6, 3, 10, 3, 8, 5, 6, 3, 6, 3, 6, 8, 3, 2, 4, 5, 3, 0};
        testArrayShunZhaoAndMineAndBerkman(A, blockSize);
    }

    return 1;
}

// [5, 2, 0, 4, 3, 9]