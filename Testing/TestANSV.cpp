//
// Created by Rolf Svenning on 18/04/2023.
//

#include "iostream"
#include "../Glue/_aux.h"
#include "../ANSV/naive_n2_work.h"
#include "../ANSV/seq_array_n_work.h"
#include "../ANSV/seq_stack_n_work.h"
#include "TestANSV.h"
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
}