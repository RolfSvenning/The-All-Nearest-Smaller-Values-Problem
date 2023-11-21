#include "naive_n2_work.h"
#include <array>

// Function computing the smaller values of an array A.
// Returns a tuple containing the left smaller values in L and right smaller values in R.
std::tuple<std::array<VI, n>, std::array<VI, n>> ANSV_naive(std::array<long, n> A) {
    std::array<VI, n> L;
    std::array<VI, n> R;

    for (int i = 0; i < A.size(); ++i) {
        L[i] = -1;
        R[i] = -1;
        // LEFT SMALLER VALUE
        for (int j = i - 1; 0 <= j; --j) {
            if (A[j] < A[i]) {
                L[i] = VI(A[j], j);
                break;
            }
        }
        // RIGHT SMALLER VALUE
        for (int j = i + 1; j < n; ++j) {
            if (A[j] < A[i]) {
                R[i] = VI(A[j], j);
                break;
            }
        }
    }
    return {L, R};
}

