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


template<typename Function>
std::tuple<parlay::sequence<long>, parlay::sequence<long>, double> ANSV_generic(Function ANSV, parlay::sequence<long> &A_, long blockSize, bool returnLR) {
    long n = A_.size();
    long *L = new long[n];
    long *R = new long[n];
    long *A = new long[n];
    parallel_for(0, n, [&] (size_t i){
        A[i] = A_[i];
    });

    double time = ANSV(A, n, L, R, blockSize);

    parlay::sequence<long> L_(n);
    parlay::sequence<long> R_(n);
    parallel_for(0, n, [&] (size_t i){
        L_[i] = L[i];
        R_[i] = R[i];
    });
    delete [] L;
    delete [] R;
    delete [] A;
    if (returnLR) return {L_, R_, time};
    else return {parlay::sequence<long>(), parlay::sequence<long>(), time};
}

void testArrayShunZhaoAndMineAndBerkman(sequence<long> A, const long blockSize) {
    cout << endl << "NEW EXPERIMENT with n, blockSize: " << A.size() << ", " << blockSize << endl;

    cout  << " --- sequential array based: ANSV --- " << endl;
    auto [L1, R1, t1] = ANSV_generic(ANSV_seq_array, A, blockSize);
    cout << "Time: " << to_string(t1) << endl;

//    cout << endl << " --- Shun & Zhao: ANSV parallel nlogn work --- " << endl;
//    auto [L2, R2, t2] = ANSV_generic(ANSV_ShunZhao, A, blockSize);
//    cout << "Time: " << to_string(t2) << endl;
//    assert(L1 == L2 and R1 == R2);

    cout << endl << " --- Shun & Zhao: (almost) original --- " << endl;
    auto [L2, R2, t2] = ANSV_generic(shunZhaoOriginal, A, blockSize);
    cout << "Time: " << to_string(t2) << endl;
    assert(L1 == L2 and R1 == R2);

//    cout << endl << " --- Mine: ANSV parallel nlogn work --- " << endl;
//    auto [L4, R4, t4] = ANSV_nlogn_mine(A, blockSize);
//    cout << "Time: " << to_string(t4) << endl;
//    assert(L3 == L4 and R3 == R4);

    cout << endl << " --- Berkman: ANSV parallel n work --- " << endl;
    auto [L3, R3, t3] = ANSV_generic(ANSV_Berkman, A, blockSize);
    cout << "Time: " << to_string(t3) << endl;

    assert(L2 == L3 and R2 == R3);
}


int testAllCorrectness(){
        for (int i = 0; i < 300; ++i) {
            auto [n, blockSize] = returnRandomAndBlocksize(312, 110);
//            long n = 4;
//            long blockSize = 2;
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

        for (int i = 0; i < 1; ++i) {
            long n = 1234567; // 123456789
            const long blockSize = 23 * 32 * 10; //TODO: only works for even block_size
            sequence<long> A = returnMergeArray(n);
//            printArray(A);
            testArrayShunZhaoAndMineAndBerkman(A, blockSize);
        }

        return 1;
}



//
//void testSequential(sequence<long> A, const long blockSize, bool verbose) {
//    bool innerVerbose = true;
//
//    internal::timer t("Time");
//    if (verbose) printArray(A);
//
////    if (innerVerbose) cout << " --- ANSV naive --- " << endl;
////    t.start();
////    auto [L1, R1] = ANSV_naive(A);
////    t.next("");
////    t.stop();
////    if (verbose) printArraysVI(list<sequence<VI>>{L1, R1});
//
//    if (innerVerbose) cout << " --- ANSV sequential array based --- " << endl;
//    t.start();
//    auto [L2, R2] = ANSV_seq_array(A);
//    t.next("");
//    t.stop();
//    if (verbose) printArraysVI(list<sequence<VI>>{L2, R2});
//
////    assert(L1 == L2 and R1 == R2);
//
//    if (innerVerbose) cout << " --- ANSV sequential stack based --- " << endl;
//    t.start();
//    auto [L3, R3] = ANSV_seq_stack(A);
//    t.next("");
//    t.stop();
//    if (verbose) printArraysVI(list<sequence<VI>>{L3, R3});
//
//    assert(L2 == L3 and R2 == R3);
//
//    if (innerVerbose) cout << " --- ANSV parallel nlogn work Shun & Zhao --- " << endl;
//    t.start();
//    auto [L4, R4] = ANSV_ShunZhao(A, blockSize);
//    t.next("");
//    t.stop();
//    if (verbose) printArraysVI(list<sequence<VI>>{L4, R4});
//
//    assert(L3 == L4 and R3 == R4);
//
//    if (innerVerbose) cout << " --- ANSV parallel nlogn work mine --- " << endl;
//    t.start();
//    auto [L5, R5] = ANSV_nlogn_mine(A, blockSize);
//    t.next("");
//    t.stop();
//
//
//    assert(L4 == L5); //TODO: right VIs
//
//    if (innerVerbose) cout << " --- All tests passed 5/5 --- " << endl << endl;
//}
//
//
//
//
//
//
//
//
//









