//
// Created by Rolf Svenning on 25/10/2023.
//

#ifndef ANSV2_BERKMANOPTIMAL_H
#define ANSV2_BERKMANOPTIMAL_H

#include "parlay/sequence.h"
#include "../Glue/VI.h"


double ANSV_Berkman(long *A, long n, long *L, long *R, long blockSize);


#endif // ANSV2_BERKMANOPTIMAL_H
