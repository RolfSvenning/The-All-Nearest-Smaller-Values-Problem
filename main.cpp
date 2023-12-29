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
#include "Experiments/experiments.h"

int main() {
//      long n = 4; // 1234567
//      const long blockSize = 4; //TODO: only works for even block_size
//      parlay::sequence<long> A = returnSortedArray(n);
//      testArrayShunZhaoAndMineAndBerkman(A, blockSize);
//    parlay::sequence<long> A = {1,1,7,8,5,4,2};
//    auto [L, R] = ANSV_Berkman(A, blockSize);
//    printArray(A);
//    printArraysVI(std::list<parlay::sequence<VI>>{L, R});

//  speedup(1, 1);
  return testAllCorrectness();
//    return 1;
}

// [5, 2, 0, 4, 3, 9]

// PARLAY_NUM_THREADS=1