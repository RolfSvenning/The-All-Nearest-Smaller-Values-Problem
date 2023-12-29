#include "naive_n2_work.h"
#include <array>

using namespace std;
using namespace parlay;

// Function computing the smaller values of an array A.
// Returns a tuple containing the left smaller values in L and right smaller values in R.
tuple<sequence<VI>, sequence<VI>>  ANSV_naive(sequence<long> A) {
    long n = A.size();
    sequence<VI> L(n);
    sequence<VI> R(n);

    parallel_for(0, n, [&] (size_t i){
        // LEFT SMALLER VALUE
        for (int j = i - 1; 0 <= j; --j) {
            if (A[j] <= A[i]) {
                L[i] = VI(A[j], j);
                break;
            }
        }

        // RIGHT SMALLER VALUE
        for (int j = i + 1; j < n; j++) {
            if (A[j] <= A[i]) {
                R[i] = VI(A[j], j);
                break;
            }
        }
    });
    return {L, R};
}

