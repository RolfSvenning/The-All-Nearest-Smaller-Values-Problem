#include "iostream"
#include <fstream>
#include "experiments.h"
#include "../Glue/data.h"
#include "../Glue/_aux.h"
#include "../Testing/TestANSV.h"
#include <thread>
#include "parlay/primitives.h"

// DATE
#include "ctime"

using namespace parlay;
using namespace std;

//const int NUMBER_OF_CORES = 12;
//const long BLOCK_SIZE = 10240; // 32 * 32 * 10
double TIMEOUT = 1; // seconds


string getCurrentDate(){
    chrono::system_clock::time_point today = chrono::system_clock::now();
    time_t tt = chrono::system_clock::to_time_t ( today );
    return ctime(&tt);
}

int writeToFile(const string& fileName, const string& text){
    auto filePath = "../Experiments/Results/" + fileName + ".txt";
    auto filePath2 = filePath.c_str();
    ofstream f (filePath.c_str(), ios_base::app);
    f << text << endl << endl;
    f.close();
    return 1;
}

tuple<long, long> largestN(const string& algorithmType, const string& inputType, long BLOCK_SIZE){ // _iobuf fp
    // TODO: https://stackoverflow.com/questions/21557479/how-to-get-environment-variables-in-c-in-a-cross-platform-way/23073039#23073039
    cout << "largestN" << endl;
    // INPUT
    long n = 65536; // 268435456 = 2^28
    sequence<long> A;
    while (true){
        try {
            internal::timer t("largestN");
            t.start();
            A = returnInputOfType(inputType, n);

            auto [L, R, time_] = ANSV_generic(algorithmType, A, BLOCK_SIZE);
            if (t.total_time() > TIMEOUT) break;
            n = 2 * n;
            cout << "n: " << n << endl;
        } catch (exception& e) {
            cout << "Caught exception: " << e.what() << endl;
            n = (long)(n / 2); //
            break;
        }
    }
    long nRes = (long)(n / 2);
    long logn = (long)log2(nRes);
    cout << "Largest n and log(n): " << nRes << ", " << logn << endl;
    return {nRes, logn};
}


void experiment(const string& filename, long n, const long BLOCK_SIZE, const string& algorithmType, const string& inputType, int repetitions){
    // TODO: GET NUMBER OF CORES FROM SYSTEM!

    // INPUT
    sequence<long> A = returnInputOfType(inputType, n);
    writeToFile(filename, "\nDate: " + getCurrentDate() + filename + " experiment with "
                                                                     "algorithm=" + algorithmType + ", inputType=" + inputType + ", repetitions=" + to_string(repetitions) +
                          ", numberOfCores=" + getenv("PARLAY_NUM_THREADS")); // to_string(-1)

    // ROUNDS
//    cout << "====== inputType: " << inputType << " ======" << endl;
    for (int i = 0; i < repetitions; ++i) {
        A = returnInputOfType(inputType, n);
        auto [L, R, res] = ANSV_generic(algorithmType, A, BLOCK_SIZE);
        writeToFile(filename, res);
    }
}


void experimentAllInputs(const string& filename, long n, const long BLOCK_SIZE, const string& algorithmType, int repetitions){
    // TODO: SET NUMBER OF CORES FROM SYSTEM!

    // INPUT
    string inputTypes[3] = {"MERGE", "SORTED", "RANDOM"};
    for (const string& inputType : inputTypes){
        experiment(filename, n, BLOCK_SIZE, algorithmType, inputType, repetitions);
    }
}

void experimentAllInputsAllAlgorithms(const string& filename, long n, const long BLOCK_SIZE, int repetitions){
    // TODO: for speedup experiment set P=1,2,3,...,maxNumberOfProcessors. SET NUMBER OF CORES FROM SYSTEM!

    // INPUT
    string algorithmTypes[4] = {"SEQUENTIAL", "SHUN_ZHAO", "SHUN_ZHAO_NO_HEURISTIC", "BERKMAN_VISHKIN"};
    for (const string& algorithmType : algorithmTypes){
//        cout << "====== algorithmType: " << algorithmType << " ======" << endl;
//        cout << "===================================================================" << endl;
        experimentAllInputs(filename, n, BLOCK_SIZE, algorithmType, repetitions);
    }
}

// N = 2^p for p = 0,1,2,...,largestPowerOfTwo - 1. P=1 and P=maxNumberOfProcessor.
void experimentRunningTime(long n, const long BLOCK_SIZE, int repetitions){
    // TODO: run for P=1 and P=maxNumberOfProcessor. SET NUMBER OF CORES FROM SYSTEM!

    for (double b : {1.7, 2.0}) {
        long p = 2;
        while ((long)pow(b, p) <= n) {
            experimentAllInputsAllAlgorithms("runningTime", (long)pow(b, p), BLOCK_SIZE, repetitions);
            p++;
        }
    }
}

// Fix N and P.
void experimentBlocksize(long n, int repetitions){
    // small block size
    for (long B = 1; B <= 64; B=B+3) {
        cout << "B: " << B << endl;
        experimentAllInputsAllAlgorithms("blockSize", n, B, repetitions);
    }

    // medium block size
    for (long B = 64; B <= 16384; B += 128) {
        cout << "B: " << B << endl;
        experimentAllInputsAllAlgorithms("blockSize", n, B, repetitions);
    }

    // large block size
    for (long B = 2; B < n; B *= 2) {
        cout << "B: " << B << endl;
        experimentAllInputsAllAlgorithms("blockSize", n, B, repetitions);
    }
}
