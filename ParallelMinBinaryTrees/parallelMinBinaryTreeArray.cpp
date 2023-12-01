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

long TtoA(long i, long d, long n){
    if (i <= n - 2 + d) return i - d + 1; //2 * n - 2 - i;
    else return i - d - n + 1;
}

long AtoT(long i, long d, long n){
    if (i < n - d) return i + n - 1 + d;
    else return i + d - 1; //i - (n - d) + n - 1;
}

std::tuple<parlay::sequence<long>,long> createBinaryTreeForInput(parlay::sequence<long>& A) {
    long n = A.size();
    //'d' is the number of input nodes on second to last layer
    long d = powl(2, ceil(log2(n))) - n;
    parlay::sequence<long> T =  parlay::tabulate(2 * n - 1, [&] (long i) {
    if (i <= n - 2)
      return -1L;
    // take from the end when filling out second to last layer
    return A[TtoA(i, d, n)];
    });
    convertToMinBinary(0, T, n);
    return {T,d};
}

long parent(long i){
    return (i - 1) / 2;
}

long child(long i, long c){
    return 2 * i + c;
}

void convertToMinBinary(long i, parlay::sequence<long>&T, long n){
    if (i > n - 2) return;
    // PARALLEL/
    if (parallel){
        parlay::par_do_if(
          i < n / 1024, // i < 512
                  [&]() { convertToMinBinary(child(i, 1), T, n);},
                 [&]() { convertToMinBinary(child(i, 2), T, n);}
        );
    } else {
        //  SEQUENTIAL
        convertToMinBinary(child(i, 1), T, n);
        convertToMinBinary(child(i, 2), T, n);
    }
    T[i] = std::min(T[child(i, 1)], T[child(i, 2)]);
}
