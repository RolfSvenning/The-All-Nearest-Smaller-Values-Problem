//
// Created by Rolf Svenning on 25/10/2023.
//

#ifndef ANSV2_BERKMANOPTIMAL_H
#define ANSV2_BERKMANOPTIMAL_H

#include "parlay/sequence.h"
#include "../Glue/VI.h"


std::tuple<parlay::sequence<long>, parlay::sequence<long>, float> ANSV_Berkman(parlay::sequence<long> &A, long blockSize);


#endif // ANSV2_BERKMANOPTIMAL_H
