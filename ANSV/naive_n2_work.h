
#ifndef IMPLEMENTATIONS_NAIVE_N_SQUARED_H
#define IMPLEMENTATIONS_NAIVE_N_SQUARED_H

#include <iostream>
#include "../Glue/VI.h"
#include "parlay/sequence.h"

std::tuple<parlay::sequence<VI>, parlay::sequence<VI>> ANSV_naive(parlay::sequence<long> A);

#endif //IMPLEMENTATIONS_NAIVE_N_SQUARED_H
