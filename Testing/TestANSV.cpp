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
#include "../ANSV/nlogn_work_mine.h"
#include "parlay/primitives.h"

void compareOutputOfNaiveSeqArraySeqStack(std::array<long, n> A, bool verbose) {
//    A = {9, 5, 2, 4, 6, 5};
    parlay::sequence<long> A_ = parlay::tabulate(n, [&] (size_t i) {return A[i];});

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
    printArraysVI(std::list<std::array<VI, n>>{L3, L4});
    for(int i=0; i < n; i++){
      assert(L3[i].ind == L4[i].ind and R3[i].ind == R4[i].ind);
    }

    std::cout << " --- ANSV parallel nlogn work mine --- " << std::endl;
    t.start();
    auto [L5, R5] = ANSV_nlogn_mine(A_);
    t.next("");
    t.stop();
//    printArraysVI({L3, L5});
    assert(L3 == L5); //TODO: check right VIs also
//    assert(L4 == L5); //TODO: check right VIs also

    std::cout << " --- All tests passed 5/5 --- " << std::endl;


}


std::tuple<std::array<VI, n>, std::array<VI, n>> testShunZhao(std::array<long, n> A_) {
  bool verbose = false;
  int L[n];
  int R[n];
  int A[n];
  for(int i=0; i < n; i++){
    A[i] = A_[i];
  }

  ComputeANSV(A, n, L, R);

  std::array<VI, n> L_;
  std::array<VI, n> R_;
  for(int i=0; i < n; i++){
    L_[i].ind = L[i];
    R_[i].ind = R[i];
  }
  return {L_, R_};
}