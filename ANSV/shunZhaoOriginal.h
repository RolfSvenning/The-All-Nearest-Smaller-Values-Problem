//
// Created by Rolf on 12/29/2023.
//

#ifndef ANSV2_SHUNZHAOORIGINAL_H
#define ANSV2_SHUNZHAOORIGINAL_H

#include "parlay/parallel.h"
#include "parlay/sequence.h"
#include "../Glue/VI.h"


std::tuple<parlay::sequence<long>, parlay::sequence<long>, float> ANSV_shunZhao_original(parlay::sequence<long> &A_, long blockSize);

#endif //ANSV2_SHUNZHAOORIGINAL_H
