
#include "seq_array_n_work.h"
#include "../Glue/_aux.h"
#include "array"
#include "parlay/primitives.h"

using namespace std;
using namespace parlay;


tuple<sequence<long>, sequence<long>, float> ANSV_seq_array(sequence<long> A) {
    long n = A.size();
    sequence<long> L(n, -1);
    sequence<long> R(n, -1);
    internal::timer t("Time");
    t.start();

    // LEFT SMALLER VALUES
    for (int i = 0; i < A.size(); ++i) {
        int j = i - 1;
        while (0 <= j) {
            if (A[j] <= A[i]) {
                L[i] = j;
                break;
            } else if (L[j] != -1) {
                j = L[j];
            } else break;
        }
    }

    // RIGHT SMALLER VALUES
    for (int i = A.size() - 1; 0 <= i; --i) {
        int j = i + 1;
        while (j < A.size()) {
            if (A[j] <= A[i]) {
                R[i] = j;
                break;
            } else if (R[j] != -1) {
                j = R[j];
            } else {
                break;
            }
        }
    }

    return {L, R, t.total_time()};
}
