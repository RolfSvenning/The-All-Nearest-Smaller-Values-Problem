#include "parlay/sequence.h"
#include "parallelMinBinaryTreeArray.h"
#include "iostream"
#include "parlay/io.h"

int main(int argc, char* argv[]) {
    parlay::sequence<long> A = generate_values(10);
    std::cout << parlay::to_chars(A) << std::endl;

    return -1;
}
