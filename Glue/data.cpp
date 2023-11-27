//
// Created by Rolf Svenning on 21/11/2023.
//

#include "data.h"
#include <array>
#include <numeric>

parlay::sequence<long> returnSortedArray(long n){
  parlay::sequence<long> A(n);
  std::iota(A.begin(), A.end(), 1);
  return A;
}

parlay::sequence<long> returnMergeArray(long n){
    parlay::sequence<long> A(n);
  int nhalf = floor(n/2);
  for (int i = 0; i < nhalf; i++){
    A[i] = i;
  }
  for (int i = nhalf; i < n; i++){
    A[i] = n - i - 1;
  }
  return A;
}
