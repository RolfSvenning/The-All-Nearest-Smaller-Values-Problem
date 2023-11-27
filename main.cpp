#include "ANSV/nlogn_work_shun_and_zhao.h"
#include "Glue/_aux.h"
#include "Glue/data.h"
#include "Testing/TestANSV.h"
#include "iostream"
#include "limits"
#include "parlay/internal/get_time.h"
#include "parlay/primitives.h"

int main() {
    for (int i = 0; i < 3; ++i) { //TODO: revert
      std::array<long, n> A = returnMergeArray();
        testAll(A, false);
    }
//    std::array<long, n> A = returnMergeArray();
//    printArray(A);
//    std::array<long, n> A = {5, 9, 12, 15, 13, 6, 10, 11, 2, 8, 1, 3, 7, 14, 4};
//    testAll(A, false);

//    long N = 25000000099;
//    parlay::sequence<long> T = parlay::tabulate(N, [&] (size_t i) {return (long) i;});
//    long sum = 0;
//    for (int i = 0; i < N; ++i) {
//      sum += T[i];
//    }
//    std::cout << sum;

    return 1;
}