  #include "ANSV/shunZhaoOriginal.h"
  #include "Glue/_aux.h"
  #include "Glue/data.h"
  #include "Testing/TestANSV.h"
  #include "iostream"
#include "Misc/test.h"
  #include "limits"
  #include "parlay/internal/get_time.h"
  #include "parlay/primitives.h"
  #include "ANSV/nlogn_work_mine.h"
  #include "ANSV/berkmanOptimal.h"
  #include "Experiments/experiments.h"
  #include "parlay/sequence.h"
#include "cstring"

using namespace std;
//using namespace parlay;

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


    int repetitions = 3;
//    string algorithmType = "SHUN_ZHAO"; // SEQUENTIAL, SHUN_ZHAO, SHUN_ZHAO_NO_HEURISTIC, BERKMAN_VISHKIN
//    experiment("speedup", n, algorithmType, "MERGE", rounds);
//    experiment("speedup", n, algorithmType, "SORTED", rounds);
//    experiment("speedup", n, algorithmType, "RANDOM", rounds);
//    experimentAllInputs("speedup", n, algorithmType, rounds);

//    long largestN(const string& algorithmType, const string& inputType, string (*ANSV)(long*, long, long*, long*, long, bool), long BLOCK_SIZE){
    assert(getenv("PARLAY_NUM_THREADS") != nullptr);
    auto [n, logn] = largestN("BERKMAN_VISHKIN", "MERGE", 8192);
    cout << "largest n:" << n << endl;
    cout << "number of threads:" << getenv("PARLAY_NUM_THREADS") << endl;
    cout << "number of threads:" << strtol(getenv("PARLAY_NUM_THREADS"), nullptr, 10) << endl;
    setenv("PARLAY_NUM_THREADS", "9", 1);
    cout << "number of threads:" << getenv("PARLAY_NUM_THREADS") << endl;
    setenv("PARLAY_NUM_THREADS", "12", 1);
    cout << "number of threads:" << getenv("PARLAY_NUM_THREADS") << endl;

    n = 65536; //2^16 = 65536 2^18 = 262144 2^20 = 1048576 2^22 = 4194304 2^24 = 16777216
//    const char *si;
//    // SPEEDUP
        for (long i = 1; i <= strtol(getenv("PARLAY_NUM_THREADS"), nullptr, 10); i++) {
        string stringIndex = to_string(i);
        char * si = new char [stringIndex.length()+1];
        std::strcpy (si, stringIndex.c_str());
        int putEnvSuccess = setenv("PARLAY_NUM_THREADS", si, 1);
        cout << "number of threads:" << getenv("PARLAY_NUM_THREADS") << endl;
        assert(putEnvSuccess == 0);
        experimentAllInputsAllAlgorithms("speedup", n, 8192, repetitions);
        delete[] si;
    }

    //     RUNNING TIME P=1, maxNumberOfProcessors
    for(long i: {1l, strtol(getenv("PARLAY_NUM_THREADS"), nullptr, 10)}){
        cout << "number of threads:" << getenv("PARLAY_NUM_THREADS") << endl;
        int putEnvSuccess = setenv("PARLAY_NUM_THREADS", to_string(i).c_str(), 1);
        assert(putEnvSuccess == 0);
        experimentRunningTime(16, 8192, repetitions);
    }
//     BLOCK SIZE 64 * 64 = 4096
    for (long i = 1; i <= strtol(getenv("PARLAY_NUM_THREADS"), nullptr, 10); i++) {
        cout << "number of threads:" << getenv("PARLAY_NUM_THREADS") << endl;
        int putEnvSuccess = setenv("PARLAY_NUM_THREADS", to_string(i).c_str(), 1);
        assert(putEnvSuccess == 0);
        experimentBlocksize(n, repetitions);
    }



//    totalTimeExperiment(1, 1);
//    int putEnvSuccess = _putenv("PARLAY_NUM_THREADS=12");
//    assert(putEnvSuccess == 0);
//    return testAllCorrectness();
//    cout << "running" << endl;
//    sequence<long> A = {1,2,3};
//    std::cout << 123 << std::endl;
//    std::cout << ftest(9) << std::endl;
    return 1;
}

// [5, 2, 0, 4, 3, 9]

// PARLAY_NUM_THREADS=1