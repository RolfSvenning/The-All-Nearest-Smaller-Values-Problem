//
// Created by Rolf Svenning on 18/04/2023.
//

#include "TestCT.h"
#include "../Cartesian_tree/CT_from_ANSV_naive.h"
#include "../Cartesian_tree/CT_from_ANSV_seq_IO.h"
#include "../ANSV/seq_stack_n_work.h"
#include "../Glue/_aux.h"
#include "iostream"

void verifyHeapAndSortedPropertyOfCT(std::array<int, n> A, bool verbose) {
    auto [L, R] = ANSV_seq_stack(A);
    std::array<Node, n> C1 = CT_from_ANSV_naive(A, L, R);
    std::array<Node, n> C2 = CT_from_ANSV_seq_IO(A, L, R);

    if (verbose) std::cout << " --- CT testing --- " << std::endl;
    if (verbose) printArray(A);
    if (verbose) std::cout << " --- CT_from_ANSV_naive --- " << std::endl;
    verifyHeapProperty(C1, verbose);
    verifySortedProperty(C1, verbose);

    if (verbose) std::cout << " --- CT_from_ANSV_seq_IO --- " << std::endl;
    verifyHeapProperty(C2, verbose);
    verifySortedProperty(C2, verbose);
    checkEqualityOfTwoCartesianTrees(C1, C2);
}

void checkEqualityOfTwoCartesianTrees(std::array<Node, n> C1, std::array<Node, n> C2) {
    for (int i = 0; i < n; ++i) {
        auto [v1, ind1, p1, l1, r1] = C1[i];
        auto [v2, ind2, p2, l2, r2] = C2[i];
        assert(v1 == v2);
        assert(ind1 == ind2);
        if (p1) {
            assert(p2);
            assert(p1->v == p2->v);
        } else assert(not p2);
        if (l1) {
            assert(l2);
            assert(l1->v == l2->v);
        } else assert(not l2);
        if (r1) {
            assert(r2);
            assert(r1->v == r2->v);
        } else assert(not r2); // TODO: Refactor to Node.h comparator
    }
}

void verifyHeapProperty(std::array<Node, n> C, bool verbose) {
    int countNodesWithNoParent = 0;
    for (Node u : C) {
        if (!u.p) {
            ++countNodesWithNoParent;
            continue;
        }
        if (u.v < u.p->v) { // Parent should be SMALLER than child
            std::cout << "u.p->v: " << u.p->v << " and u.v: " << u.v << std::endl;
            assert (u.p->v < u.v);
        }
    }
    if (countNodesWithNoParent != 1) {
        std::cout << "countNodesWithNoParent: " << countNodesWithNoParent << std::endl;
    }
    assert(countNodesWithNoParent == 1);
}

void verifySortedProperty(std::array<Node, n> C, bool verbose) {
    for (Node u : C) {
        if (u.l) {
            if (u.l->ind > u.ind) { // Left child should be SMALLER than parent
                std::cout << "u.l->ind: " << u.l->ind << " and u.ind: " << u.ind << std::endl;
                assert (u.l->ind < u.ind);
            }
        }
        if (u.r) {
            if (u.r->ind < u.ind) { // Right child should be BIGGER than parent
                std::cout << "u.l->ind: " << u.r->ind << " and u.ind: " << u.ind << std::endl;
                assert (u.r->ind > u.ind);
            }
        }
    }
}



