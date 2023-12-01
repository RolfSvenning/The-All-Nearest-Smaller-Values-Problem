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
//    long n = 1239; // 1234567
//    const long blockSize = 10; //TODO: only works for even block_size

    for (int i = 0; i < 100; ++i) {
        auto [n, blockSize] = returnRandomNandBlocksize();
        parlay::sequence<long> A = returnRandomArray(n);
        testArrayShunZhaoAndMine(A, blockSize);
    }


    return 1;
}