//
// Created by Rolf Svenning on 25/10/2023.
//

#include "berkmanOptimal.h"
#include "parlay/io.h"
#include "parlay/parallel.h"

parlay::sequence<long> hardcodedInputOfLength16(){
  // { 0  1  2  3  --  4  5  6  7  --   8  9 10 11  --  12 13 14 15}
  // {15  0  8  3  -- 11 12 14 13  --  10  9  6  8  --   7  2  1  4} # merging for example 0 8 3 with 2 1 (split by 6)
  return parlay::sequence<long>{15, 0, 8, 3, 11, 12, 14, 13, 10, 9, 6, 8, 7, 2, 1, 4};
}

parlay::sequence<long> getInput(int dataType){
  if (dataType == 0) return hardcodedInputOfLength16();
  else assert(0 == 1);
}

int main(int argc, char* argv[]) {
    // ------------ SETUP ------------
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

    // ------------ INPUT ------------
    parlay::sequence<long> A = getInput(dataType);
    std::cout << "A: " << parlay::to_chars(A) << std::endl;

    // ------------ STEP 1: GROUPS ------------
    // divides input into groups of size log(n) and finds local matches
    // and smallest element in group for the min-binary tree.
    long s = ceil(log2(n));
    long Gn = ceil(n / s);

    parlay::blocked_for(0, n, s, [&] (size_t blockNumber, size_t i, size_t j) {
      for (int k = i; k < j; k++){
        std::cout << k << std::endl;
      }
});


//        return parlay::tabulate(2 * n - 1, [&] (long i) {
//          if (i <= n - 2) return -1L;
//          auto r = gen[i];
//          return dis(r);
//        });




    return 7;
}