
#include "seq_array_n_work.h"
#include "../Glue/_aux.h"
#include "array"
#include "parlay/primitives.h"

using namespace std;
using namespace parlay;


double ANSV_seq_array(long *A, long n, long *L, long *R, long blockSize) {
    internal::timer t("Time");
    t.start();

    // LEFT SMALLER VALUES
    for (int i = 0; i < n; ++i) {
        L[i] = -1;
        int j = i - 1;
        while (0 <= j) {
            if (A[j] <= A[i]) {
                L[i] = j;
                break;
            } else if (L[j] != -1) j = L[j];
            else break;
        }
    }

    // RIGHT SMALLER VALUES
    for (int i = n - 1; 0 <= i; --i) {
        R[i] = -1;
        int j = i + 1;
        while (j < n) {
            if (A[j] <= A[i]) {
                R[i] = j;
                break;
            } else if (R[j] != -1) j = R[j];
            else break;
        }
    }

    return t.total_time();
}

