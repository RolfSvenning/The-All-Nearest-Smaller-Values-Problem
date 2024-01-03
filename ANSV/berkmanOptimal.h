
#ifndef ANSV2_BERKMANOPTIMAL_H
#define ANSV2_BERKMANOPTIMAL_H

#include "parlay/sequence.h"
#include "../Glue/VI.h"


std::string ANSV_Berkman(long *A, long n, long *L, long *R, long blockSize, bool usingHeuristic);


#endif // ANSV2_BERKMANOPTIMAL_H
