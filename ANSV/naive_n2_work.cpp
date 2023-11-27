#include "naive_n2_work.h"
#include <array>

// Function computing the smaller values of an array A.
// Returns a tuple containing the left smaller values in L and right smaller values in R.
std::tuple<parlay::sequence<VI>, parlay::sequence<VI>>  ANSV_naive(parlay::sequence<long> A) {
    long n = A.size();
    parlay::sequence<VI> L(n);
    parlay::sequence<VI> R(n);
    for (int i = 0; i < A.size(); i++) {
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
    }
    return {L, R};
}

