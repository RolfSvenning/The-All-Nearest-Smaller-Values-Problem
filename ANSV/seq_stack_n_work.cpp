
#include "seq_stack_n_work.h"
#include "../Glue/_aux.h"
#include "stack"
#include "parlay/primitives.h"

using namespace std;
using namespace parlay;

// string ANSV_seq_array(long *A, long n, long *L, long *R, long blockSize, bool usingHeuristic) {
//std::tuple<parlay::sequence<VI>, parlay::sequence<VI>> ANSV_seq_stack(parlay::sequence<long> A){
std::string ANSV_seq_stack(long *A, long n, long *L, long *R, long blockSize, bool usingHeuristic) {
    internal::timer t("Time");
    t.start();

    // LEFT SMALLER VALUES
    std::stack<long> S1;
    for (int i = n - 1; 0 <= i; --i) {
        L[i] = -1;
        while (!S1.empty()) {
            long j = S1.top();
            if (A[i] <= A[j]) { // S1: <- i...j...
                L[j] = i;
                S1.pop();
            } else break;
        }
        S1.push( i);
    }

    // RIGHT SMALLER VALUES
    std::stack<long> S2;
    for (int i = 0; i < n; ++i) {
        R[i] = -1;
        while (!S2.empty()) {
            long j = S2.top();
            if (A[i] <= A[j]) { // S2: ...j...i ->
                R[j] = i;
                S2.pop();
            } else break;
        }
        S2.push(i);
    }

    double totalTime = t.total_time();
    string res = " --- Sequential_stack --- with n, blockSize, heuristic: "
                 + to_string(n) + ", " + to_string(blockSize) + ", " + to_string(usingHeuristic) + "\n"
                 + "Total time: " + to_string(totalTime) + "\n";
//    cout << res << endl;
    return res;
}

