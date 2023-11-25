#include "Glue/_aux.h"
#include "Testing/TestANSV.h"
#include "iostream"
#include "limits"
#include "Glue/data.h"
#include "ANSV/nlogn_work_shun_and_zhao.h"
#include "parlay/internal/get_time.h"

int main() {
    for (int i = 0; i < 0; ++i) { //TODO: revert
      std::array<long, n> A = returnRandomArray();
      //    std::array<int, n> A = {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3}; //set constants to 16
        testAll(A, false);
      //
      //    testShunZhao(A);
    }
    //    std::array<int, n> A = {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3}; //set constants to 16
    std::array<long, n> A = returnMergeArray();
    printArray(A);
    testAll(A, false);
//    int n = 80000;
//    int L[n];
//    int R[n];
//    int A[n];
//    for(int i=0; i < n; i++){
//        A[i] = i;
//    }


//    parlay::internal::timer t("Time ");
//    t.start();
//    testShunZhao(A);
//    t.next("");
//    t.stop();

    return 1;
}