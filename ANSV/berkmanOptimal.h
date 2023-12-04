//
// Created by Rolf Svenning on 25/10/2023.
//

#ifndef ANSV2_BERKMANOPTIMAL_H
#define ANSV2_BERKMANOPTIMAL_H

#include "parlay/sequence.h"

// INPUT FUNCTIONS
parlay::sequence<long> hardcodedInputOfLength16();

parlay::sequence<long> getInput(int dataType);

std::tuple<parlay::sequence<VI>, parlay::sequence<VI>> ANSV_Berkman(parlay::sequence<long> &A, const long blockSize);

// ALGORITHM FUNCTIONS

#endif // ANSV2_BERKMANOPTIMAL_H
