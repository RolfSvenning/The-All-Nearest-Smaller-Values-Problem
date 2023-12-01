#include "ANSV/nlogn_work_shun_and_zhao.h"
#include "Glue/_aux.h"
#include "Glue/data.h"
#include "Testing/TestANSV.h"
#include "iostream"
#include "limits"
#include "parlay/internal/get_time.h"
#include "parlay/primitives.h"
#include "ANSV/nlogn_work_mine.h"

int main() {
    long n = 1239; // 1234567
    const long blockSize = 10; //TODO: only works for even block_size

    for (int i = 0; i < 10; ++i) { //TODO: revert
// RANDOM N AND BLOCK SIZE
//      std::random_device rd; // obtain a random number from hardware
//      std::mt19937 gen(rd()); // seed the generator
//      std::uniform_int_distribution<> dn(2, 1234567); // define the range
//      long n = dn(gen);
//      std::uniform_int_distribution<> db(2, std::max(40000, (int)n)); // define the range
//      long blockSize = 2 * db(gen); //TODO: only works for even block_size


        parlay::sequence<long> A = returnRandomArray(n);
//      auto [L,R] = ANSV_ShunZhao(A);
//      std::cout << L[32].v << std::endl;
        testArrayShunZhaoAndMine(A, blockSize);
//        testAll(A);
        //

    }

//    std::array<long, n> A = returnMergeArray();

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