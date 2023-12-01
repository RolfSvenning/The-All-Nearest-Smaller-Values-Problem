#ifndef ANSV2_DATA_H
#define ANSV2_DATA_H

#include "parlay/sequence.h"

parlay::sequence<long> returnSortedArray(long n);

parlay::sequence<long> returnMergeArray(long n);

std::tuple<long, long> returnRandomNandBlocksize();

#endif // ANSV2_DATA_H

