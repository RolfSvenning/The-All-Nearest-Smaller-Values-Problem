//
// Created by Rolf Svenning on 18/04/2023.
//

#ifndef IMPLEMENTATIONS_TESTCT_H
#define IMPLEMENTATIONS_TESTCT_H


#include "../Glue/Node.h"
#include "../Glue/_constants.h"

void verifyHeapAndSortedPropertyOfCT(std::array<int, n> A, bool verbose = false);

void verifyHeapProperty(std::array<Node, n> C, bool verbose = false);

void verifySortedProperty(std::array<Node, n> C, bool verbose = false);

void checkEqualityOfTwoCartesianTrees(std::array<Node, n> C1, std::array<Node, n> C2);

#endif //IMPLEMENTATIONS_TESTCT_H
