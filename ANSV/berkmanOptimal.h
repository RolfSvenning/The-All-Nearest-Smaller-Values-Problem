//
// Created by Rolf Svenning on 25/10/2023.
//

#ifndef ANSV2_BERKMANOPTIMAL_H
#define ANSV2_BERKMANOPTIMAL_H

#include "parlay/sequence.h"
#include "../Glue/VI.h"

// INPUT FUNCTIONS
parlay::sequence<long> hardcodedInputOfLength16();

parlay::sequence<long> getInput(int dataType);

void farAwayBlocks_ANSV_linear(parlay::sequence<long> &A, long a, long b, long c, long d, parlay::sequence<VI> &L, parlay::sequence<VI> &R);

std::tuple<parlay::sequence<VI>, parlay::sequence<VI>> ANSV_Berkman(parlay::sequence<long> &BCi, const long blockSize);

// ALGORITHM FUNCTIONS

#endif // ANSV2_BERKMANOPTIMAL_H
