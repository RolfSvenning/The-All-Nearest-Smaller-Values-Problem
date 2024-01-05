#include "iostream"
#include "parlay/primitives.h"
#include "../Glue/_aux.h"
#include "../Glue/data.h"
#include "TestANSV.h"
#include "../ANSV/seq_array_n_work.h"
#include "../ANSV/shunZhaoOriginal.h"
#include "../ANSV/berkmanOptimal.h"


using namespace std;
using namespace parlay;


std::tuple<parlay::sequence<long>, parlay::sequence<long>, string> ANSV_generic(const string& algorithmType, parlay::sequence<long> &A_, long blockSize) {
    long n = A_.size();
    long *L = new long[n];
    long *R = new long[n];
    long *A = new long[n];
    parallel_for(0, n, [&] (size_t i){
        A[i] = A_[i];
    });

    string time;
    if      (algorithmType == "SEQUENTIAL")             time = ANSV_seq_array(A, n, L, R, blockSize, true);
    else if (algorithmType == "SHUN_ZHAO")              time = ANSV_ShunZhao( A, n, L, R, blockSize, true);
    else if (algorithmType == "SHUN_ZHAO_NO_HEURISTIC") time = ANSV_ShunZhao( A, n, L, R, blockSize, false);
    else if (algorithmType == "BERKMAN_VISHKIN")        time = ANSV_Berkman(  A, n, L, R, blockSize, true);
    else {
        cout << "ERROR: algorithmType not recognized" << endl;
        assert(1 == 0);
    }

    parlay::sequence<long> L_(n);
    parlay::sequence<long> R_(n);
    parallel_for(0, n, [&] (size_t i){
        L_[i] = L[i];
        R_[i] = R[i];
    });
    delete [] L;
    delete [] R;
    delete [] A;
    return {L_, R_, time};
}

void testArrayShunZhaoAndMineAndBerkman(sequence<long> A, const long blockSize) {
    cout << endl << "NEW EXPERIMENT with n, blockSize: " << A.size() << ", " << blockSize << endl << endl;

//    cout  << " --- sequential array based: ANSV --- " << endl;
    // --- sequential array based: ANSV ---
    auto [L1, R1, res1] = ANSV_generic("SEQUENTIAL", A, blockSize);
    cout << res1 << endl;

    // --- Shun & Zhao: with heuristic ---
    auto [L2, R2, res2] = ANSV_generic("SHUN_ZHAO", A, blockSize);
    cout << res2 << endl;
    assert(L1 == L2 and R1 == R2);

    // --- Shun & Zhao: without heuristic ---
    auto [L3, R3, res3] = ANSV_generic("SHUN_ZHAO_NO_HEURISTIC", A, blockSize);
    cout << res3 << endl;
    assert(L2 == L3 and R2 == R3);

    // --- Berkman: ANSV parallel n work ---
    auto [L4, R4, res4] = ANSV_generic("BERKMAN_VISHKIN", A, blockSize);
    cout << res4 << endl;
    assert(L3 == L4 and R3 == R4);
}


int testAllCorrectness(){
//    for (int i = 0; i < 400; ++i) {
//        auto [n, blockSize] = returnRandomAndBlocksize(10 , 10);
//        sequence<long> A = returnRandomArray(n);
//        testArrayShunZhaoAndMineAndBerkman(A, blockSize);
//    }
//
//    for (int i = 0; i < 200; ++i) {
//        auto [n, blockSize] = returnRandomAndBlocksize(100 , 100);
//        sequence<long> A = returnRandomArray(n);
//        testArrayShunZhaoAndMineAndBerkman(A, blockSize);
//    }
//
//    for (int i = 0; i < 100; ++i) {
//        auto [n, blockSize] = returnRandomAndBlocksize(10000, 10000);
//        sequence<long> A = returnRandomArray(n);
//        testArrayShunZhaoAndMineAndBerkman(A, blockSize);
//    }
//
//    for (int i = 0; i < 10; ++i) {
//        auto [n, blockSize] = returnRandomAndBlocksize(1000000, 10000);
//        sequence<long> A = returnRandomArray(n);
//        testArrayShunZhaoAndMineAndBerkman(A, blockSize);
//    }

    long n = 100000000;
    long blockSize = 8192; // 4096 * 16 = 65536
    sequence<long> A2 = returnSortedArray(n);
    testArrayShunZhaoAndMineAndBerkman(A2, blockSize);
    sequence<long> A3 = returnMergeArray(n);
    testArrayShunZhaoAndMineAndBerkman(A3, blockSize);

        return 1;
}








