#ifndef IMPLEMENTATIONS_SEQ_STACK_H
#define IMPLEMENTATIONS_SEQ_STACK_H

#include "iostream"
#include "../Glue/VI.h"
#include <tuple>
#include "parlay/sequence.h"

std::string ANSV_seq_stack(long *A, long n, long *L, long *R, long blockSize, bool usingHeuristic);

#endif //IMPLEMENTATIONS_SEQ_STACK_H
