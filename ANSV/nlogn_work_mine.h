//
// Created by Rolf Svenning on 21/11/2023.
//

#ifndef ANSV2_ANSV_NLOGN_WORK_CPP_H
#define ANSV2_ANSV_NLOGN_WORK_CPP_H

#include "parlay/sequence.h"
#include "../Glue/VI.h"

using namespace parlay;

long findLeftMatch(long n, const sequence<long> &T, long d, sequence<long> &L, int i, long start=-1);

long findRightMatch(long n, const sequence<long> &T, long d, sequence<long> &R, int i, long start=-1);

void ComputeANSV_Linear(sequence<long> &A, long n, sequence<long> &L, sequence<long> &R, long offset);

std::tuple<sequence<long>, sequence<long>, float> ANSV_nlogn_mine(sequence<long> &A, long blockSize);

#endif // ANSV2_ANSV_NLOGN_WORK_CPP_H
