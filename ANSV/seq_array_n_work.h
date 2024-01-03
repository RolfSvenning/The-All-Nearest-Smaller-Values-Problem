


#ifndef IMPLEMENTATIONS_SEQ_ARRAY_H
#define IMPLEMENTATIONS_SEQ_ARRAY_H

#include "iostream"
#include "../Glue/VI.h"
#include "parlay/sequence.h"

std::string ANSV_seq_array(long *A, long n, long *L, long *R, long blockSize, bool usingHeuristic);

#endif //IMPLEMENTATIONS_SEQ_ARRAY_H
