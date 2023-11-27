#ifndef IMPLEMENTATIONS_SEQ_STACK_H
#define IMPLEMENTATIONS_SEQ_STACK_H

#include "../Glue/VI.h"
#include "iostream"
#include <tuple>
#include "parlay/sequence.h"

std::tuple<parlay::sequence<VI>, parlay::sequence<VI>> ANSV_seq_stack(parlay::sequence<long> A);

#endif //IMPLEMENTATIONS_SEQ_STACK_H
