//
// Created by Rolf Svenning on 12/04/2023.
//
#include "list"
#include "VI.h"
#include "parlay/sequence.h"

#ifndef IMPLEMENTATIONS_AUX_H
#define IMPLEMENTATIONS_AUX_H

void printParlayArrayVI(parlay::sequence<VI> A, std::string s);

bool isPowerOfTwo(long x);

void printArraysVI(const std::list<parlay::sequence<VI>>& AS);

void printArrayVI(parlay::sequence<VI> A);

void printArray(parlay::sequence<long> A);


//std::tuple<std::array<VI, n>, std::array<VI, n>> seqToArray(std::tuple<parlay::sequence<VI>, parlay::sequence<VI>> LR);


#endif //IMPLEMENTATIONS_AUX_H
