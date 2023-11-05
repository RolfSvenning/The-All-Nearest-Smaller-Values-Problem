//
// Created by Rolf Svenning on 25/10/2023.
//

//#include "berkmanOptimal.h"
#include "parlay/parallel.h"

int main(int argc, char* argv[]) {
    // SETUP
    if (argc != 3){
        std::cout << "Usage: missing 'n' or 'dataType' argument." << std::endl;
        return 0;
    }

    long n;
    try { n = std::stol(argv[1]); }
    catch (...) { std::cout << "argument 'n' malformed" << std::endl; return 1; }
    // for simplicity; this guarantees the input will be stored in its original order at the leaves
    assert (pow(2,floor(log2(n))) == n);

    int dataType;
    try { dataType = std::stol(argv[2]); }
    catch (...) { std::cout << "parameter dataType malformed (should be small integer)" << std::endl; return 1; }
    assert (dataType >= 0 and dataType <= 5);
    std::cout << "n and dataType: " << n << " " << dataType << std::endl;

    parlay::sequence<long> A = generate_values(n, dataType);


    return 7;
}