#include "Glue/_aux.h"
#include "Testing/TestANSV.h"
#include "iostream"
#include "limits"

int main() {
    int imax = std::numeric_limits<int>::max();

    std::array<long, n> A = returnRandomArray();
//    std::array<int, n> A = {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3}; //set constants to 16
    compareOutputOfNaiveSeqArraySeqStack(A, false);
//
//    testShunZhao(A);
    return 7;
}