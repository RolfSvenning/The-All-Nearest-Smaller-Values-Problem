#include "iostream"
#include <fstream>
#include "experiments.h"
#include "../Glue/data.h"
#include "../Testing/TestANSV.h"
#include <thread>

// Algorithms
#include "../ANSV/shunZhaoOriginal.h"
#include "../ANSV/berkmanOptimal.h"

// DATE
#include "ctime"
#include "chrono"

using namespace parlay;
using namespace std;

const int NUMBER_OF_CORES = thread::hardware_concurrency();
const long BLOCK_SIZE = 10240; // 32 * 32 * 10
double TIMEOUT = 1;

template<typename Function>
void totalTimeExperiment(Function Experiment, int rounds, int repetitions){
    cout << "Speedup experiment with rounds, repetitions: " << rounds << ", " << repetitions << endl;
    // CREATE FILE
    auto fileName = "../Experiments/Results/test_rounds" + to_string(rounds) + "_reps" + to_string(repetitions) + ".txt";
    auto fileName2 = fileName.c_str();
    ofstream f (fileName2);
    auto fp = fopen(fileName.c_str(), "w");

    // DATE
    chrono::system_clock::time_point today = chrono::system_clock::now();
    time_t tt = chrono::system_clock::to_time_t ( today );
    string date = ctime(&tt);
    const char *dateFinal = date.c_str();
    fputs(dateFinal, fp);

    // RUN EXPERIMENT
    Experiment(rounds, fp);

    // WRITE DATE
    f.close();
}


// Try increasing input sizes of powers of two and fix n to be the second-largest input which terminates in 5 seconds.
// For i = 1 to NUMBER_OF_CORES repeat REPETITIONS times. Store all results in array R.
// Return
//template<typename Function>
long largestN(double (*ANSV)(long*, long, long*, long*, long)){ // _iobuf fp
    // TODO: https://stackoverflow.com/questions/21557479/how-to-get-environment-variables-in-c-in-a-cross-platform-way/23073039#23073039

    // INPUT
    long n = 65536; // 268435456 = 2^28
    double time = 0;
    parlay::sequence<long> A;
    while (time < TIMEOUT){
        try {
            A = returnMergeArray(n);
            auto [L, R, time_] = ANSV_generic(ANSV, A, BLOCK_SIZE, false);
            time = time_;
            n = 2 * n;
            cout << "n: " << n << endl;
        } catch (exception& e) {
            cout << "Caught exception: " << e.what() << endl;
            n = (long)(n / 2); //
            break;
        }
    }
    long nRes = (long)(n / 2);
    cout << "Largest n is: " << nRes << endl;
    return nRes; //TODO: divide by 2
}

long speedup(double (*ANSV)(long*, long, long*, long*, long), int rounds){ // _iobuf fp
     cout << "PARLAY_NUM_THREADS: " << getenv("PARLAY_NUM_THREADS") << endl;

    int putEnvSuccess = _putenv("PARLAY_NUM_THREADS=12");
    assert(putEnvSuccess == 0);
    long n = largestN(ANSV);
//    cout << "n: " << n << endl;
    cout << "number of processors: " <<  NUMBER_OF_CORES << endl;
    assert(NUMBER_OF_CORES > 0);
    parlay::sequence<long> A = returnMergeArray(n);

//    auto *res = new double[NUMBER_OF_CORES];
    for (int i = 0; i < NUMBER_OF_CORES; ++i) {
//        cout << "PARLAY_NUM_THREADS: " << getenv("PARLAY_NUM_THREADS") << endl;
        cout << "i: " << i << endl;
        const string senv = "PARLAY_NUM_THREADS=" + to_string(i + 1);
//        cout << "senv: " << senv << endl;
        const char* env = senv.c_str();
//        _putenv("PARLAY_NUM_THREADS=6");
        _putenv(env);
        A = returnMergeArray(n);
        auto [L, R, time_] = ANSV_generic(ANSV, A, BLOCK_SIZE, false);
//        cout << "time: " << time_ << endl;
//        cout << "number of processors: " <<  thread::hardware_concurrency() << endl;
//        res[i] = time_;

    }
//    cout << "res: " << res << endl;
//    delete [] res;
    return 1;
}


