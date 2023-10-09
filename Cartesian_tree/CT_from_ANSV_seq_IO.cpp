//
// Created by Rolf Svenning on 19/04/2023.
//

#include "stack"
#include "../Glue/VI.h"
#include "../Glue/CT.h"
#include "CT_from_ANSV_seq_IO.h"

std::array<Node, n> CT_from_ANSV_seq_IO(std::array<int, n> A, std::array<VI, n> L, std::array<VI, n> R) {
    std::array<Node, n> C;
    std::stack<CT> S1;
    for (int i = 0; i < n; ++i) {
        C[i].v = A[i];
        C[i].ind = i;

        // LEFT CHILD POINTERS (using right parent pointers)
        if (not S1.empty() and S1.top().indTo == i) {
            C[i].l = S1.top().childPtr;
            S1.pop();
        }

        auto [lv, li] = L[i];
        auto [rv, ri] = R[i];
        // PARENT POINTER
        // Largest (of left and right) smaller value is the parent (only one may exist, ow. compare lv and rv)
        if ((li != -1 and ri == -1) or (li != -1 and rv < lv)) {
            C[i].p = &C[li];
        } else if (li != -1 or ri != -1) {
            C[i].p = &C[ri];
            S1.push(CT(&C[i],ri));
        }
    }

    assert(S1.empty());

    for (int i = n - 1; 0 <= i; --i) {
        // LEFT CHILD POINTERS (using right parent pointers)
        if (not S1.empty() and S1.top().indTo == i) {
            C[i].r = S1.top().childPtr;
            S1.pop();
        }

        auto [lv, li] = L[i];
        auto [rv, ri] = R[i];
        // PARENT POINTER
        // Largest (of left and right) smaller value is the parent (only one may exist, ow. compare lv and rv)
        if ((li != -1 and ri == -1) or (li != -1 and rv < lv)) {
            S1.push(CT(&C[i],li));
        }
    }

//    if (not S1.empty()) std::cout << S1.top().indTo;
    assert(S1.empty());

    return C;
}
