
#include "iostream"

#include "Experiments/experiments.h"
#include "Glue/_aux.h"
#include "Glue/data.h"
#include "Testing/TestANSV.h"


using namespace std;
using namespace parlay;

int main(int argc, char* argv[]) {
  if (argc < 5) {
    std::cerr << "Usage: " << argv[0] << " <experiment_type> <n> <block_size> <repetitions>\n";
    return 1;
  }


  // "SEQUENTIAL" "SEQUENTIAL_STACK" "SHUN_ZHAO" "SHUN_ZHAO_NO_HEURISTIC" "BERKMAN_VISHKIN"
//  string experimentType = argv[1];
  string inputType = argv[1]; // shuffledMerge or random
  long n = atol(argv[2]);
  long blockSize = atol(argv[3]);
//  int repetitions = atoi(argv[4]);
  string algorithmType = argv[4]; // SHUN_ZHAO or BERKMAN_VISHKIN
  // print input arguments
  cout << "Input arguments: " << inputType << " " << n << " " << blockSize << " " << algorithmType << endl;


      // string ANSV_generic_experiments(const string& algorithmType, parlay::sequence<long> &A_, long blockSize) {
  // input
  parlay::sequence<long> A;
  if (inputType == "shuffledMerge") {
    A = returnShuffledMergeArray(n);
  } else if (inputType == "random") {
    A = returnRandomArray(n);
  } else {
    cerr << "Invalid input type\n";
    return -1;
  }
  string time = ANSV_generic_experiments(algorithmType, A, blockSize);
  cout << time << endl;
//  sequence<long> returnRandomArray(long n);

  //
  //        // EXPERIMENTS
  //        if (experimentType == "speedup") {
  //            // SPEEDUP // Fix N //
  //            experimentSpeedup(n, -1, repetitions);
  //        } else if (experimentType == "running_time") {
  //            // RUNNING TIME // Fix P=1, maxNumberOfProcessors. //
  //            experimentRunningTime(n, blockSize, repetitions);
  //        } else if (experimentType == "block_size") {
  //            // BLOCK SIZE // Fix N and P. //
  //            experimentBlocksize(n, blockSize, repetitions);
  //        } else {
  //          cerr << "Invalid experiment type\n";
  //          return -1;
  //        }
//  return testAllCorrectness();
  //return 1;
}

