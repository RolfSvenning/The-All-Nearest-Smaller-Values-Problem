  #include "ANSV/nlogn_work_shun_and_zhao.h"
  #include "ANSV/shunZhaoOriginal.h"
  #include "Glue/_aux.h"
  #include "Glue/data.h"
  #include "Testing/TestANSV.h"
  #include "iostream"
  #include "limits"
  #include "parlay/internal/get_time.h"
  #include "parlay/primitives.h"
  #include "ANSV/nlogn_work_mine.h"
  #include "ANSV/berkmanOptimal.h"
  #include "Experiments/experiments.h"
 #include "parlay/sequence.h"

using namespace std;
using namespace parlay;

int main() {
//    long n = 4; // 1234567
//    const long blockSize = 4;
//    sequence<long> A = returnSortedArray(n);
//    testArrayShunZhaoAndMineAndBerkman(A, blockSize);
//    sequence<long> A = {1,1,7,8,5,4,2};
//    auto [L, R] = ANSV_Berkman(A, blockSize);
//    printArray(A);
//    printArraysVI(list<sequence<VI>>{L, R});


//    long n = 16777216; // 2^24 = 16777216 2^22 = 4194304 2^20 = 1048576 2^18 = 262144 2^16 = 65536
    int rounds = 3;
//    string algorithmType = "SHUN_ZHAO"; // SEQUENTIAL, SHUN_ZHAO, SHUN_ZHAO_NO_HEURISTIC, BERKMAN_VISHKIN
//    experiment("speedup", n, algorithmType, "MERGE", rounds);
//    experiment("speedup", n, algorithmType, "SORTED", rounds);
//    experiment("speedup", n, algorithmType, "RANDOM", rounds);
//    experimentAllInputs("speedup", n, algorithmType, rounds);

    // SPEEDUP
    experimentAllInputsAllAlgorithms("speedup", 16777216, 8192, rounds);

    // RUNNING TIME
    experimentRunningTime(24, 8192, rounds);

    // BLOCK SIZE 64 * 64 = 4096
    experimentBlocksize(1048576, rounds);


//    totalTimeExperiment(1, 1);
//    int putEnvSuccess = _putenv("PARLAY_NUM_THREADS=12");
//    assert(putEnvSuccess == 0);
//    return testAllCorrectness();
//    cout << "running" << endl;
//    sequence<long> A = {1,2,3};
//    cout << A[1] << endl;
    return 1;
}

// [5, 2, 0, 4, 3, 9]

// PARLAY_NUM_THREADS=1