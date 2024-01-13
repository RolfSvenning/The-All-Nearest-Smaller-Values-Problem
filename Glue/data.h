#ifndef ANSV2_DATA_H
#define ANSV2_DATA_H

#include "parlay/sequence.h"

parlay::sequence<long> returnSortedArray(long n);

parlay::sequence<long> returnMergeArray(long n);

parlay::sequence<long> returnShuffledMergeArray(long n);

parlay::sequence<long> returnRandomArray(long n);

parlay::sequence<long> returnInputOfType(std::string inputType, long n);

std::tuple<long, long> returnRandomAndBlocksize(long nMax=12345, long blockSizeMax=40000);


#endif // ANSV2_DATA_H

