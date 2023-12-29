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
#include "../ANSV/shunZhaoOriginal.h"

using namespace std;
using namespace parlay;

void testArrayShunZhaoAndMineAndBerkman(sequence<long> A, const long blockSize) {
    cout << endl << "NEW EXPERIMENT with n, blockSize: " << A.size() << ", " << blockSize << endl;
    internal::timer t("Time");

    cout  << " --- sequential array based: ANSV --- " << endl;
    t.start();
    auto [L1, R1] = ANSV_seq_array(A);
    t.next("");
    t.stop();

    cout << endl << " --- Shun & Zhao: ANSV parallel nlogn work --- " << endl;
    t.start();
    auto [L2, R2] = ANSV_ShunZhao(A, blockSize);
    t.next("");
    t.stop();


    assert(L1 == L2 and R1 == R2);

    cout << endl << " --- Mine: ANSV parallel nlogn work --- " << endl;
    t.start();
    auto [L3, R3] = ANSV_nlogn_mine(A, blockSize);
    t.next("");
    t.stop();

    assert(L2 == L3 and R2 == R3);

    cout << endl << " --- Berkman: ANSV parallel n work --- " << endl;
    t.start();
    auto [L4, R4] = ANSV_Berkman(A, blockSize);
    t.next("");
    t.stop();

    assert(L3 == L4 and R3 == R4);

    cout << endl << " --- Shun & Zhao: (almost) original --- " << endl;
//    t.start();
    auto [L5, R5, t5] = ANSV_shunZhao_orginal(A, blockSize);
    cout << "Time: " << to_string(t5) << endl;
    //    t.next("");
//    t.stop();

    if (L4 != L5) {
        printArray(A);
        printArraysVI(list<sequence<VI>>{L4, L5});
    }

    assert(L4 == L5 and R4 == R5);
}

int testAllCorrectness(){
        for (int i = 0; i < 100; ++i) {
            auto [n, blockSize] = returnRandomAndBlocksize(14, 14);
            sequence<long> A = returnDistinctRandomArray(n);
    //        sequence<long> A = returnMergeArray(n);
            testArrayShunZhaoAndMineAndBerkman(A, blockSize);
        }
        for (int i = 0; i < 20; ++i) {
            auto [n, blockSize] = returnRandomAndBlocksize(12345, 1234);
    //        long n = 39;
    //        long blockSize = 400;
            // TODO: duplicate values actually hard to fix
            sequence<long> A = returnDistinctRandomArray(n);
            // TRY BELOW INPUT
    //        sequence<long> A = {1, 7, 8, 7, 1, 6, 6, 3, 10, 3, 8, 5, 6, 3, 6, 3, 6, 8, 3, 2, 4, 5, 3, 0};
            testArrayShunZhaoAndMineAndBerkman(A, blockSize);
        }

        for (int i = 0; i < 3; ++i) {
            long n = 52345678; // 1234567
            const long blockSize = 23 * 32 * 4; //TODO: only works for even block_size
            sequence<long> A = returnSortedArray(n);
            testArrayShunZhaoAndMineAndBerkman(A, blockSize);
        }

        return 1;
}

void testSequential(sequence<long> A, const long blockSize, bool verbose) {
    bool innerVerbose = true;

    internal::timer t("Time");
    if (verbose) printArray(A);

//    if (innerVerbose) cout << " --- ANSV naive --- " << endl;
//    t.start();
//    auto [L1, R1] = ANSV_naive(A);
//    t.next("");
//    t.stop();
//    if (verbose) printArraysVI(list<sequence<VI>>{L1, R1});

    if (innerVerbose) cout << " --- ANSV sequential array based --- " << endl;
    t.start();
    auto [L2, R2] = ANSV_seq_array(A);
    t.next("");
    t.stop();
    if (verbose) printArraysVI(list<sequence<VI>>{L2, R2});

//    assert(L1 == L2 and R1 == R2);

    if (innerVerbose) cout << " --- ANSV sequential stack based --- " << endl;
    t.start();
    auto [L3, R3] = ANSV_seq_stack(A);
    t.next("");
    t.stop();
    if (verbose) printArraysVI(list<sequence<VI>>{L3, R3});

    assert(L2 == L3 and R2 == R3);

    if (innerVerbose) cout << " --- ANSV parallel nlogn work Shun & Zhao --- " << endl;
    t.start();
    auto [L4, R4] = ANSV_ShunZhao(A, blockSize);
    t.next("");
    t.stop();
    if (verbose) printArraysVI(list<sequence<VI>>{L4, R4});

    assert(L3 == L4 and R3 == R4);

    if (innerVerbose) cout << " --- ANSV parallel nlogn work mine --- " << endl;
    t.start();
    auto [L5, R5] = ANSV_nlogn_mine(A, blockSize);
    t.next("");
    t.stop();


    assert(L4 == L5); //TODO: right VIs

    if (innerVerbose) cout << " --- All tests passed 5/5 --- " << endl << endl;
}


















