//
// Created by Rolf Svenning on 18/04/2023.
//

#include "iostream"
#include "../Glue/_aux.h"
#include "../ANSV/naive_n2_work.h"
#include "../ANSV/seq_array_n_work.h"
#include "../ANSV/seq_stack_n_work.h"
#include "TestANSV.h"
#include "../ANSV/nlogn_work_shun_and_zhao.h"

#include "parlay/primitives.h"

void compareOutputOfNaiveSeqArraySeqStack(std::array<int, n> A, bool verbose) {
    parlay::internal::timer t("Time ");
    if (verbose) printArray(A);

    std::cout << " --- ANSV naive --- " << std::endl;
    t.start();
    auto [L1, R1] = ANSV_naive(A);
    t.next("");
    t.stop();
    if (verbose) printArraysVI(std::list<std::array<VI, n>>{L1, R1});

    std::cout << " --- ANSV sequential array based --- " << std::endl;
    t.start();
    auto [L2, R2] = ANSV_seq_array(A);
    t.next("");
    t.stop();
    if (verbose) printArraysVI(std::list<std::array<VI, n>>{L2, R2});

    assert(L1 == L2 and R1 == R2);

    std::cout << " --- ANSV sequential stack based --- " << std::endl;
    t.start();
    auto [L3, R3] = ANSV_seq_stack(A);
    t.next("");
    t.stop();
    if (verbose) printArraysVI(std::list<std::array<VI, n>>{L3, R3});

    assert(L2 == L3 and R2 == R3);

    std::cout << " --- ANSV parallel nlogn work Shun & Zhao --- " << std::endl;
    t.start();
    auto [L4, R4] = testShunZhao(A); //TODO: only sets indices, not values!
    t.next("");
    t.stop();
    if (verbose) printArraysVI(std::list<std::array<VI, n>>{L4, R4});
}


std::tuple<std::array<VI, n>, std::array<VI, n>> testShunZhao(std::array<int, n> A_) {
  bool verbose = false;
  int L[n];
  int R[n];
  int A[n];
  for(int i=0; i < n; i++){
    A[i] = A_[i];
  }

  ComputeANSV(A, n, L, R);

  // Print the elements of the array
  if (verbose) {
    std::cout << "A" << std::endl;
    for (int i : A) {
        std::cout << i << ' ';
    }

    std::cout << std::endl << "L" << std::endl;
    for (int i : L) {
        std::cout << i << ' ';
    }

    std::cout << std::endl << "R" << std::endl;
    for (int i : R) {
        std::cout << i << ' ';
    }
  }

  std::array<VI, n> L_;
  std::array<VI, n> R_;
  for(int i=0; i < n; i++){
    L_[i].ind = L[i];
    R_[i].ind = R[i];
  }
  return {L_, R_};
}
