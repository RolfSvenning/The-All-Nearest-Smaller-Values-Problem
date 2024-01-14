#include "Glue/_aux.h"
#include "iostream"
#include "Experiments/experiments.h"
#include "Glue/data.h"

using namespace std;
using namespace parlay;

int main(int argc, char* argv[]) {
  if (argc < 5) {
    std::cerr << "Usage: " << argv[0] << " <experiment_type> <n> <block_size> <repetitions>\n";
    return 1;
  }
//  auto [size, logSize] = largestN("BERKMAN_VISHKIN", "MERGE", 8192);
//        cout << "largest n:" << size << endl;

//  sequence<long> A = returnShuffledMergeArray(100);
//  printArray(A);


  string experimentType = argv[1];
  long n = atol(argv[2]);
  long blockSize = atol(argv[3]);
  int repetitions = atoi(argv[4]);

        // EXPERIMENTS
        if (experimentType == "speedup") {
            // SPEEDUP // Fix N //
            experimentSpeedup(n, blockSize, repetitions);
        } else if (experimentType == "running_time") {
            // RUNNING TIME // Fix P=1, maxNumberOfProcessors. //
            experimentRunningTime(n, blockSize, repetitions);
        } else if (experimentType == "block_size") {
            // BLOCK SIZE // Fix N and P. //
            experimentBlocksize(n, repetitions);
        } else {
          cerr << "Invalid experiment type\n";
          return -1;
        }
    return 1;
}
// PARLAY_NUM_THREADS=1



////    long largestN(const string& algorithmType, const string& inputType, string (*ANSV)(long*, long, long*, long*, long, bool), long BLOCK_SIZE){
//assert(getenv("PARLAY_NUM_THREADS") != nullptr);
////    auto [n, logn] = largestN("BERKMAN_VISHKIN", "MERGE", 8192);
//cout << "largest n:" << n << endl;
//cout << "number of threads:" << getenv("PARLAY_NUM_THREADS") << endl;
//cout << "number of threads:" << strtol(getenv("PARLAY_NUM_THREADS"), nullptr, 10) << endl;
//setenv("PARLAY_NUM_THREADS", "9", 1);
//cout << "number of threads:" << getenv("PARLAY_NUM_THREADS") << endl;
//setenv("PARLAY_NUM_THREADS", "12", 1);
//cout << "number of threads:" << getenv("PARLAY_NUM_THREADS") << endl;
//
////    n = 65536; //2^16 = 65536 2^18 = 262144 2^20 = 1048576 2^22 = 4194304 2^24 = 16777216
////    const char *si;
////    // SPEEDUP
//for (long i = 1; i <= strtol(getenv("PARLAY_NUM_THREADS"), nullptr, 10); i++) {
//  string stringIndex = to_string(i);
//  char * si = new char [stringIndex.length()+1];
//  std::strcpy (si, stringIndex.c_str());
//  int putEnvSuccess = setenv("PARLAY_NUM_THREADS", si, 1);
//  cout << "number of threads:" << getenv("PARLAY_NUM_THREADS") << endl;
//  assert(putEnvSuccess == 0);
//  experimentAllInputsAllAlgorithms("speedup", n, 8192, repetitions);
//}
//
////     RUNNING TIME P=1, maxNumberOfProcessors
//for(long i: {1l, strtol(getenv("PARLAY_NUM_THREADS"), nullptr, 10)}){
//  cout << "number of threads:" << getenv("PARLAY_NUM_THREADS") << endl;
//  int putEnvSuccess = setenv("PARLAY_NUM_THREADS", to_string(i).c_str(), 1);
//  assert(putEnvSuccess == 0);
//  experimentRunningTime(16, 8192, repetitions);
//}

//    long n = 4; // 1234567
//    const long blockSize = 4;
//    sequence<long> A = returnSortedArray(n);
//    testArrayShunZhaoAndMineAndBerkman(A, blockSize);
//    sequence<long> A = {1,1,7,8,5,4,2};
//    auto [L, R] = ANSV_Berkman(A, blockSize);
//    printArray(A);
//    printArraysVI(list<sequence<VI>>{L, R});


//    long n = 16777216; // 2^24 = 16777216 2^22 = 4194304 2^20 = 1048576 2^18 = 262144 2^16 = 65536


//    totalTimeExperiment(1, 1);
//    int putEnvSuccess = _putenv("PARLAY_NUM_THREADS=12");
//    assert(putEnvSuccess == 0);
//    return testAllCorrectness();
//    cout << "running" << endl;
//    sequence<long> A = {1,2,3};
//    std::cout << 123 << std::endl;
//    std::cout << ftest(9) << std::endl;


//    int repetitions = 3;
//    string algorithmType = "SHUN_ZHAO"; // SEQUENTIAL, SHUN_ZHAO, SHUN_ZHAO_NO_HEURISTIC, BERKMAN_VISHKIN
//    experiment("speedup", n, algorithmType, "MERGE", rounds);
//    experiment("speedup", n, algorithmType, "SORTED", rounds);
//    experiment("speedup", n, algorithmType, "RANDOM", rounds);
//    experimentAllInputs("speedup", n, algorithmType, rounds);
