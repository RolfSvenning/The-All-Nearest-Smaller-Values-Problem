
#include "seq_array_n_work.h"
#include "../Glue/_aux.h"
#include "array"


std::tuple<std::array<VI, n>, std::array<VI, n>> ANSV_seq_array(std::array<int, n> A) {
    std::array<VI, n> L = {};
    std::array<VI, n> R = {};

    // LEFT SMALLER VALUES
    for (int i = 0; i < A.size(); ++i) {
//        L[i] = -1;
        int j = i - 1;
        while (0 <= j) {
            if (A[j] < A[i]) {
                L[i] = VI(A[j], j);
                break;
            } else if (L[j].ind != -1) {
                j = L[j].ind;
            } else break;
        }
    }

    // RIGHT SMALLER VALUES
    for (int i = A.size() - 1; 0 <= i; --i) {
//        R[i] = -1;
        int j = i + 1;
        while (j < A.size()) {
            if (A[j] < A[i]) {
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
