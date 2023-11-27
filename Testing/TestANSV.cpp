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

void testAll(std::array<long, n> A, bool verbose) {
    bool innerVerbose = true;
    parlay::sequence<long> A_ = parlay::tabulate(n, [&] (size_t i) {return A[i];});

    parlay::internal::timer t("Time ");
    if (verbose) printArray(A);

    if (innerVerbose) std::cout << " --- ANSV naive --- " << std::endl;
    t.start();
    auto [L1, R1] = ANSV_naive(A);
    t.next("");
    t.stop();
    if (verbose) printArraysVI(std::list<std::array<VI, n>>{L1, R1});

    if (innerVerbose) std::cout << " --- ANSV sequential array based --- " << std::endl;
    t.start();
    auto [L2, R2] = ANSV_seq_array(A);
    t.next("");
    t.stop();
    if (verbose) printArraysVI(std::list<std::array<VI, n>>{L2, R2});

    assert(L1 == L2 and R1 == R2);

    if (innerVerbose) std::cout << " --- ANSV sequential stack based --- " << std::endl;
    t.start();
    auto [L3, R3] = ANSV_seq_stack(A);
    t.next("");
    t.stop();
    if (verbose) printArraysVI(std::list<std::array<VI, n>>{L3, R3});

    assert(L2 == L3 and R2 == R3);

    if (innerVerbose) std::cout << " --- ANSV parallel nlogn work Shun & Zhao --- " << std::endl;
    t.start();
    auto [L4, R4] = ANSV_ShunZhao(A);
    t.next("");
    t.stop();
    if (verbose) printArraysVI(std::list<std::array<VI, n>>{L4, R4});

    assert(L3 == L4 and R3 == R4);

    if (innerVerbose) std::cout << " --- ANSV parallel nlogn work mine --- " << std::endl;
    t.start();
    auto [L5, R5] = ANSV_nlogn_mine(A_);
    t.next("");
    t.stop();

    assert(L4 == L5); //TODO: right VIs

    if (innerVerbose) std::cout << " --- All tests passed 5/5 --- " << std::endl << std::endl;
}


