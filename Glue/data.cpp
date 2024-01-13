
#include "data.h"
#include <array>
#include <numeric>
#include "random"
#include "parlay/primitives.h"

using namespace std;
using namespace parlay;

sequence<long> returnSortedArray(long n){
  sequence<long> A(n);
  iota(A.begin(), A.end(), 1);
  return A;
}

sequence<long> returnMergeArray(long n){
    sequence<long> A = tabulate(n, [&](size_t i) {
        if (i < floor(n/2)) return (long)(2 * i);
        else return (long)(2 * (n - i - 1) + 1);
    });
  return A;
}

sequence<long> returnShuffledMergeArray(long n){
  random_device rd1;
  mt19937 gen1(rd1());
  uniform_int_distribution<long> dis1(0, INT_MAX);

  random_generator gen(dis1(gen1));
  uniform_int_distribution<long> dis(0, 1);

  sequence<long> A = returnMergeArray(n);

  for (int i = 0; i < n; i = i + 2) {
      auto r = gen[i];
        if (dis(r) == 1) swap(A[i], A[i + 1]);
  }
  return A;
}

sequence<long> returnRandomArray(long n) {
    random_device rd1;
    mt19937 gen1(rd1());
    uniform_int_distribution<long> dis1(0, INT_MAX);

    random_generator gen(dis1(gen1));
    uniform_int_distribution<long> dis(0, INT_MAX);
    sequence<long> A = tabulate(ceil(1.2 * n), [&](size_t i) {
        auto r = gen[i];
        return dis(r);
    });

    A = remove_duplicates(A);
    A = A.subseq(0, n);
    assert(A.size() == n);
    return A;
}

sequence<long> returnInputOfType(string inputType, long n) {
    if (inputType == "SORTED") return returnSortedArray(n);
    else if (inputType == "MERGE") return returnMergeArray(n);
    else if (inputType == "SHUFFLED_MERGE") return returnShuffledMergeArray(n);
    else if (inputType == "RANDOM") return returnRandomArray(n);
    else {
        cout << "Invalid input type: " << inputType << endl;
        exit(1);
    }
}

tuple<long, long> returnRandomAndBlocksize(long nMax, long blockSizeMax){
    // RANDOM N AND BLOCK SIZE
    random_device rd; // obtain a random number from hardware
    mt19937 gen(rd()); // seed the generator
    uniform_int_distribution<> dn(2, nMax); // define the range
    long n = dn(gen);
//    uniform_int_distribution<> db(1, min((int)blockSizeMax/2, (int)n/2)); // define the range
    uniform_int_distribution<> db(1, blockSizeMax); // define the range
    long blockSize = db(gen);
    return {n, blockSize};
}




//// Returns an array containing a random permutation of [0...n-1]
//sequence<long> returnDistinctRandomArray(long n) {
//    sequence<long> A = tabulate(n, [&](size_t i) { return (long)i; });
//
//    // Shuffle the array by swapping with previous element with probability 1/(n-1)
//    random_device rd;
//    mt19937 gen(rd());
//    for (int i = 1; i < n; ++i) {
//        uniform_real_distribution<> dis(0.0, 1.0);
//        if (dis(gen) > 1.0 / (i - 1)) {
//            // Seed the random number generator
//            random_device rd2;
//            mt19937 gen2(rd2());
//            // Define the uniform distribution
//            uniform_int_distribution<int> dist2(0, i - 1);
//
//            // Generate a random integer from 0 to i - 1 (inclusive)
//            int randomNum = dist2(gen2);
//
//            swap(A[i], A[randomNum]);
//        }
//    }
//    return A;
//}