//
// Created by Rolf Svenning on 18/04/2023.
//

#include "iostream"
#include "../Glue/_aux.h"
#include "../Glue/data.h"
#include "../ANSV/naive_n2_work.h"
#include "../ANSV/seq_array_n_work.h"
#include "../ANSV/seq_stack_n_work.h"
#include "TestANSV.h"
#include "../ANSV/nlogn_work_shun_and_zhao.h"
#include "../ANSV/nlogn_work_mine.h"
#include "parlay/primitives.h"
#include "../ANSV/berkmanOptimal.h"

void testSequential(parlay::sequence<long> A, const long blockSize, bool verbose) {
    bool innerVerbose = true;

    parlay::internal::timer t("Time");
    if (verbose) printArray(A);

//    if (innerVerbose) std::cout << " --- ANSV naive --- " << std::endl;
//    t.start();
//    auto [L1, R1] = ANSV_naive(A);
//    t.next("");
//    t.stop();
//    if (verbose) printArraysVI(std::list<parlay::sequence<VI>>{L1, R1});

    if (innerVerbose) std::cout << " --- ANSV sequential array based --- " << std::endl;
    t.start();
    auto [L2, R2] = ANSV_seq_array(A);
    t.next("");
    t.stop();
    if (verbose) printArraysVI(std::list<parlay::sequence<VI>>{L2, R2});

//    assert(L1 == L2 and R1 == R2);

    if (innerVerbose) std::cout << " --- ANSV sequential stack based --- " << std::endl;
    t.start();
    auto [L3, R3] = ANSV_seq_stack(A);
    t.next("");
    t.stop();
    if (verbose) printArraysVI(std::list<parlay::sequence<VI>>{L3, R3});

    assert(L2 == L3 and R2 == R3);

    if (innerVerbose) std::cout << " --- ANSV parallel nlogn work Shun & Zhao --- " << std::endl;
    t.start();
    auto [L4, R4] = ANSV_ShunZhao(A, blockSize);
    t.next("");
    t.stop();
    if (verbose) printArraysVI(std::list<parlay::sequence<VI>>{L4, R4});

    assert(L3 == L4 and R3 == R4);

    if (innerVerbose) std::cout << " --- ANSV parallel nlogn work mine --- " << std::endl;
    t.start();
    auto [L5, R5] = ANSV_nlogn_mine(A, blockSize);
    t.next("");
    t.stop();

    assert(L4 == L5); //TODO: right VIs

    if (innerVerbose) std::cout << " --- All tests passed 5/5 --- " << std::endl << std::endl;
}

void testArrayShunZhaoAndMineAndBerkman(parlay::sequence<long> A, const long blockSize) {
    std::cout << std::endl << "NEW EXPERIMENT with n, blockSize: " << A.size() << ", " << blockSize << std::endl;
    parlay::internal::timer t("Time");

    std::cout  << " --- sequential array based: ANSV --- " << std::endl;
    t.start();
    auto [L1, R1] = ANSV_seq_array(A);
    t.next("");
    t.stop();

    std::cout << std::endl << " --- Shun & Zhao: ANSV parallel nlogn work --- " << std::endl;
    t.start();
    auto [L2, R2] = ANSV_ShunZhao(A, blockSize);
    t.next("");
    t.stop();


    assert(L1 == L2 and R1 == R2);

    std::cout << std::endl << " --- Mine: ANSV parallel nlogn work --- " << std::endl;
    t.start();
    auto [L3, R3] = ANSV_nlogn_mine(A, blockSize);
    t.next("");
    t.stop();

    assert(L2 == L3 and R2 == R3);

    std::cout << std::endl << " --- Berkman: ANSV parallel n work --- " << std::endl;
    t.start();
    auto [L4, R4] = ANSV_Berkman(A, blockSize);
    t.next("");
    t.stop();

    assert(L3 == L4 and R3 == R4);
}

int testAllCorrectness(){
        for (int i = 0; i < 10; ++i) {
            auto [n, blockSize] = returnRandomNandBlocksize(80000, 800);
            parlay::sequence<long> A = returnDistinctRandomArray(n);
    //        parlay::sequence<long> A = returnMergeArray(n);
            testArrayShunZhaoAndMineAndBerkman(A, blockSize);
        }
        for (int i = 0; i < 1000; ++i) {
            auto [n, blockSize] = returnRandomNandBlocksize(100, 100);
    //        long n = 39;
    //        long blockSize = 400;
            // TODO: duplicate values actually hard to fix
            parlay::sequence<long> A = returnDistinctRandomArray(n);
            // TRY BELOW INPUT
    //        parlay::sequence<long> A = {1, 7, 8, 7, 1, 6, 6, 3, 10, 3, 8, 5, 6, 3, 6, 3, 6, 8, 3, 2, 4, 5, 3, 0};
            testArrayShunZhaoAndMineAndBerkman(A, blockSize);
        }

        for (int i = 0; i < 3; ++i) {
            long n = 22345678; // 1234567
            const long blockSize = 23 * 32; //TODO: only works for even block_size
            parlay::sequence<long> A = returnSortedArray(n);
            testArrayShunZhaoAndMineAndBerkman(A, blockSize);
        }

        return 1;
}



















