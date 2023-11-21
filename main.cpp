#include "Glue/_aux.h"
#include "Testing/TestANSV.h"
#include "iostream"
#include "limits"
#include "Glue/data.h"

int main() {
    for (int i = 0; i < 0; ++i) { //TODO: revert
      std::array<long, n> A = returnRandomArray();
      //    std::array<int, n> A = {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3}; //set constants to 16
      compareOutputOfNaiveSeqArraySeqStack(A, false);
      //
      //    testShunZhao(A);
    }
    std::array<long, n> A = returnMergeArray();
    //    std::array<int, n> A = {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3}; //set constants to 16
    compareOutputOfNaiveSeqArraySeqStack(A, false);
    return 1;
}