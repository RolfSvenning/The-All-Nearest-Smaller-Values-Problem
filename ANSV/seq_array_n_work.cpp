
#include "seq_array_n_work.h"
#include "../Glue/_aux.h"
#include "array"


std::tuple<parlay::sequence<VI>, parlay::sequence<VI>> ANSV_seq_array(parlay::sequence<long> A) {
    long n = A.size();
    parlay::sequence<VI> L(n);
    parlay::sequence<VI> R(n);

    // LEFT SMALLER VALUES
    for (int i = 0; i < A.size(); ++i) {
        int j = i - 1;
        while (0 <= j) {
            if (A[j] <= A[i]) {
                L[i] = VI(A[j], j);
                break;
            } else if (L[j].ind != -1) {
                j = L[j].ind;
            } else break;
        }
    }

    // RIGHT SMALLER VALUES
    for (int i = A.size() - 1; 0 <= i; --i) {
        int j = i + 1;
        while (j < A.size()) {
            if (A[j] <= A[i]) {
                R[i] = VI(A[j], j);
                break;
            } else if (R[j].ind != -1) {
                j = R[j].ind;
            } else {
                break;
            }
        }
    }

    return {L, R};
}
