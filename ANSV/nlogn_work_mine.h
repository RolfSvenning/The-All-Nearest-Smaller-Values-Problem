//
// Created by Rolf Svenning on 21/11/2023.
//

#ifndef ANSV2_ANSV_NLOGN_WORK_CPP_H
#define ANSV2_ANSV_NLOGN_WORK_CPP_H

#include "parlay/sequence.h"
#include "../Glue/VI.h"

void findLeftMatch(long n, const parlay::sequence<long> &T, long d, parlay::sequence<VI> &L, int i, long start);

void findRightMatch(long n, const parlay::sequence<long> &T, long d, parlay::sequence<VI> &R, int i, long start);

std::tuple<parlay::sequence<VI>, parlay::sequence<VI>> ANSV_nlogn_mine(parlay::sequence<long> &A, const long blockSize);

int main2(int argc, char* argv[]);
#endif // ANSV2_ANSV_NLOGN_WORK_CPP_H
