//
// Setting number of threads: PARLAY_NUM_THREADS=x
//

#include "parallelMinBinaryTreeArray.h"
#include <iostream>
#include "parlay/primitives.h"
#include "parlay/random.h"
#include "parlay/sequence.h"
#include "parlay/io.h"
#include "../Glue/_aux.h"

bool parallel = true;

parlay::sequence<long> generateValues(long n) {
    parlay::random_generator gen(1);
    std::uniform_int_distribution<long> dis(0, n-1);

    assert(isPowerOfTwo(n));
    return parlay::tabulate(2 * n - 1, [&] (long i) {
        if (i <= n - 2) return -1L;
        auto r = gen[i];
        return dis(r);
    });
}

long treeIndexToArrayIndex(long i, long d){
    if (i <= n - 2 + d) return i - d + 1; //2 * n - 2 - i;
    else return i - d - n + 1;
}

std::tuple<parlay::sequence<long>,long> createBinaryTreeForInput(parlay::sequence<long>& A) {
    unsigned long n = A.size();
    //'d' is the number of input nodes on second to last layer
    long d = powl(2, ceil(log2(n))) - n;
//    std::cout << powl(2, ceil(log2(n))) - n << std::endl;
//    std::cout << "d ceillogn n lowceillogn" << std::endl;
//    std::cout << powl(2, ceill(log2(n))) -n << std::endl;
//    std::cout << d << " " << ceil(log2(n)) << " " << n << " " << powl(2, ceil(log2(n)) - n) + 0.5 << std::endl;
    parlay::sequence<long> T =  parlay::tabulate(2 * n - 1, [&] (long i) {
    if (i <= n - 2)
      return -1L;
    // take from the end when filling out second to last layer
    return A[treeIndexToArrayIndex(i, d)];
    });
    return {T,d};
}

long parent(long i){
    return (i - 1) / 2;
}

long child(long i, long c){
    assert (1 <= c and c <=2);
    return 2 * i + c;
}

void fixNode(int i, parlay::sequence<long>& A, long n){
    if (i > n - 2) return;
    // PARALLEL
    if (parallel){
        parlay::par_do_if(i < n / 1024, // i < 512
                          [&]() {fixNode(child(i, 1), A, n);},
                          [&]() {fixNode(child(i, 2), A, n);}
        );
    } else {
        //  SEQUENTIAL
        fixNode(child(i, 1), A, n);
        fixNode(child(i, 2), A, n);
    }
    A[i] = std::min(A[child(i, 1)], A[child(i, 2)]);
}


int main2(int argc, char* argv[]){
    auto usage = "Usage: missing 'n' argument. "
                 "Creating parallel min binary tree of n elements <n>";
    if (argc != 2){
        std::cout << usage << std::endl;
        return 0;
    }

    long n;
    try { n = std::stol(argv[1]); }
    catch (...) { std::cout << usage << std::endl; return 1; }
    parlay::internal::timer t("Time");


//  std::cout << "1)" << std::endl;
//  std::cout << parlay::to_chars(values) << std::endl;

    parlay::sequence<long> values = generateValues(n);
    t.start();
    fixNode(0, values, n);
    t.next("min binary tree");

//    std::cout << "2)" << std::endl;
//    std::cout << parlay::to_chars(values) << std::endl;
//    std::cout << "parallel: " << parallel << std::endl;
    return 0;
}

