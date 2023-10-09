#include "Glue/_aux.h"
#include "Testing/TestANSV.h"
#include "iostream"
#include "limits"

int main() {
    int imax = std::numeric_limits<int>::max();
    std::cout << "max int size: " << imax << std::endl;

    std::cout << "Hello world" << std::endl;
    std::array<int, n> A = returnRandomArray();
    compareOutputOfNaiveSeqArraySeqStack(A);
}