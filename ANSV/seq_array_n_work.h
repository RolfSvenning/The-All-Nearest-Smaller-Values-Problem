


#ifndef IMPLEMENTATIONS_SEQ_ARRAY_H
#define IMPLEMENTATIONS_SEQ_ARRAY_H

#include "iostream"
#include "../Glue/VI.h"
#include "parlay/sequence.h"

std::tuple<parlay::sequence<long>, parlay::sequence<long>, float> ANSV_seq_array(parlay::sequence<long> A);

#endif //IMPLEMENTATIONS_SEQ_ARRAY_H
