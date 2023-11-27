


#ifndef IMPLEMENTATIONS_SEQ_ARRAY_H
#define IMPLEMENTATIONS_SEQ_ARRAY_H

#include "../Glue/VI.h"
#include "iostream"
#include "parlay/sequence.h"

std::tuple<parlay::sequence<VI>, parlay::sequence<VI>> ANSV_seq_array(parlay::sequence<long> A);

#endif //IMPLEMENTATIONS_SEQ_ARRAY_H
