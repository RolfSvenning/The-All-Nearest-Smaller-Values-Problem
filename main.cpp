
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
  string experimentType = argv[1];
  long n = atol(argv[2]);
  long blockSize = atol(argv[3]);
  int repetitions = atoi(argv[4]);


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
  return testAllCorrectness();
  //return 1;
}

