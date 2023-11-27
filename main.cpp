#include "Glue/_aux.h"
#include "Testing/TestANSV.h"
#include "iostream"
#include "limits"
#include "Glue/data.h"
#include "ANSV/nlogn_work_shun_and_zhao.h"
#include "parlay/internal/get_time.h"

int main() {
    for (int i = 0; i < 100000; ++i) { //TODO: revert
      std::array<long, n> A = returnRandomArray();
        testAll(A, false);
    }
//    std::array<long, n> A = returnMergeArray();
//    printArray(A);
//    std::array<long, n> A = {5, 9, 12, 15, 13, 6, 10, 11, 2, 8, 1, 3, 7, 14, 4};
//    testAll(A, false);

    return 1;
}