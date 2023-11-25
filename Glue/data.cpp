//
// Created by Rolf Svenning on 21/11/2023.
//

#include "data.h"
#include <array>
#include <numeric>

std::array<long, n> returnSortedArray(){
  std::array<long, n> A{};
  std::iota(A.begin(), A.end(), 1);
  return A;
}

std::array<long, n> returnMergeArray(){
  std::array<long, n> A{};
  int nhalf = floor(n/2);
  for (int i = 0; i < nhalf; i++){
    A[i] = i;
  }
  for (int i = nhalf; i < n; i++){
    A[i] = n - i - 1;
  }
//  for(int i = 0; i < n; i++){
//    std::cout << A[i] << " ";
//  }
//  std::cout << std::endl << A.size();

  return A;
}
