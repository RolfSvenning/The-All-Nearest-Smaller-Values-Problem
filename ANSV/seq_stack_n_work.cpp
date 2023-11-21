
#include "seq_stack_n_work.h"
#include "../Glue/_aux.h"
#include "stack"

std::tuple<std::array<VI, n>, std::array<VI, n>> ANSV_seq_stack(std::array<long, n> A) {
    std::array<VI, n> L = {};
    std::array<VI, n> R = {};

    // LEFT SMALLER VALUES
    std::stack<VI> S1;
    for (int i = A.size() - 1; 0 <= i; --i) {
        while (!S1.empty()) {
            VI aj = S1.top();
            if (A[i] < aj.v) { // S1: <- i...j...
                L[aj.ind] = VI(A[i], i);
                S1.pop();
            } else break;
        }
        S1.push(VI(A[i], i));
    }

    // RIGHT SMALLER VALUES
    std::stack<VI> S2;
    for (int i = 0; i < A.size(); ++i) {
        while (!S2.empty()) {
            VI aj = S2.top();
            if (A[i] < aj.v) { // S2: ...j...i ->
                R[aj.ind] = VI(A[i], i);
                S2.pop();
            } else break;
        }
        S2.push(VI(A[i], i));
    }

    return {L, R};
}

