//
// Created by Rolf Svenning on 12/04/2023.
//
#include "iostream"
#include <array>
#include <list>
#include "random"
#include "algorithm"
#include <cmath>
#include "_aux.h"
#include "_constants.h"

void printArrayVI(std::array<VI,n> A) {
    for (VI a : A)
        std::cout << a.ind << " ";
    std::cout << std::endl;
}

void printArraysVI(const std::list<std::array<VI,n>>& arrays) {
    for (std::array<VI,n> A : arrays) {
        printArrayVI(A);
    }
}

void printArray(std::array<int, n> A) {
    for (int a : A)
        std::cout << a << " ";
    std::cout << std::endl;
}

// Returns an array containing a random permutation of [0...n-1]
std::array<int, n> returnRandomArray() {
    std::array<int, n> A = {};
    for (int i = 0; i < A.size(); ++i) {
        A[i] = i + 1;
    }

    // Shuffle the array by swapping with previous element with probability 1/(n-1)
    std::random_device rd;
    std::mt19937 gen(rd());
    for (int i = 1; i < n; ++i) {
        std::uniform_real_distribution<> dis(0.0, 1.0);
        if (dis(gen) > 1.0 / (i - 1)) {
            // Seed the random number generator
            std::random_device rd2;
            std::mt19937 gen2(rd2());
            // Define the uniform distribution
            std::uniform_int_distribution<int> dist2(0, i - 1);

            // Generate a random integer from 0 to i - 1 (inclusive)
            int randomNum = dist2(gen2);

            std::swap(A[i], A[randomNum]);
        }
    }

    return A;
}