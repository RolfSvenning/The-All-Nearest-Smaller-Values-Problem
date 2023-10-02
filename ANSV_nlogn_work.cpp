#include "parlay/primitives.h"
#include "parlay/sequence.h"
#include <iostream>
//#include "test.h"


int main(int argc, char* argv[]){
//    test t1{4};
    parlay::sequence<long> A(10);
    A[5] = 2;

//    std::cout << t1.age << std::endl;
    std::cout << A[5] << std::endl;
    std::cout << A[5] << std::endl;
    return 0;
}