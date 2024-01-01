//
// Created by Rolf Svenning on 15/12/2023.
//

#ifndef ANSV2_EXPERIMENTS_H
#define ANSV2_EXPERIMENTS_H

int totalTimeExperiment(int rounds, int repetitions);

//long largestN(double (*ANSV)(long*, long, long*, long*, long)); // _iobuf fp

long speedup(double (*ANSV)(long*, long, long*, long*, long), int rounds); // _iobuf fp

#endif // ANSV2_EXPERIMENTS_H
