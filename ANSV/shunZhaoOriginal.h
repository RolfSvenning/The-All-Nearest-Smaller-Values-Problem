//
// Created by Rolf on 12/29/2023.
//

#ifndef ANSV2_SHUNZHAOORIGINAL_H
#define ANSV2_SHUNZHAOORIGINAL_H

#include "parlay/parallel.h"
#include "parlay/sequence.h"
#include "../Glue/VI.h"

inline long getLeft_opt(long **table, long depth, long n, long index, long start);
inline long getRight_opt(long **table, long depth, long n, long index, long start);
void ComputeANSV_Linear(long a[], long n, long leftElements[], long rightElements[], long offset);
long cflog2(long i);
std::string ANSV_ShunZhao(long *A, long n, long *left, long *right, long blockSize, bool usingHeuristic);

// additions for Berkman & Vishkin
std::tuple<long **, long> createBinaryTree(long *A, long n);

#endif //ANSV2_SHUNZHAOORIGINAL_H
