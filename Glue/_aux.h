//
// Created by Rolf Svenning on 12/04/2023.
//
#include "_constants.h"
#include "list"
#include "VI.h"
#include "parlay/sequence.h"

#ifndef IMPLEMENTATIONS_AUX_H
#define IMPLEMENTATIONS_AUX_H

void printParlayArrayVI(parlay::sequence<VI> A, std::string s);

bool isPowerOfTwo(long x);

void printArraysVI(const std::list<std::array<VI, n>>& arrays);

void printArrayVI(std::array<VI, n> A);

void printArray(std::array<long, n> A);

std::array<long, n> returnRandomArray();


#endif //IMPLEMENTATIONS_AUX_H
