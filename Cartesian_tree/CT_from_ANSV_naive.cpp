//
// Created by Rolf Svenning on 17/04/2023.
//

#include "CT_from_ANSV_naive.h"
#include "iostream"


std::array<Node, n> CT_from_ANSV_naive(std::array<int, n> A, std::array<VI, n> L, std::array<VI, n> R) {
    std::array<Node, n> C; // add {}? https://stackoverflow.com/questions/18295302/default-initialization-of-stdarray
    for (int i = 0; i < n; ++i) {
        C[i].v = A[i];
        C[i].ind = i;
        auto [lv, li] = L[i];
        auto [rv, ri] = R[i];
        // Largest (of left and right) smaller value is the parent (only one may exist, ow. compare lv and rv)
        if ((li != -1 and ri == -1) or (li != -1 and rv < lv)) {
            C[i].p = &C[li];
            C[li].r = &C[i];
        } else if (li != -1 or ri != -1) {
            C[i].p = &C[ri];
            C[ri].l = &C[i];
        }
    }
    return C;
}

//        if (li != -1) {
//            if (ri != -1) {
//                // both smaller values exists. Parent is larger of the two
//                if (lv < rv) {
//                    C[i].p = &C[ri];
//                    C[ri].l = &C[i];
//                } else {
//                    C[i].p = &C[li];
//                    C[li].r = &C[i];
//                }
//            } else {
//                // only left smaller value exists
//                C[i].p = &C[li];
//                C[li].r = &C[i];
//            }
//        } if (ri != -1) {
//            // only right smaller value exists
//            C[i].p = &C[ri];
//            C[ri].l = &C[i];
//        }
//    }