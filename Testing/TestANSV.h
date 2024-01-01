
#ifndef IMPLEMENTATIONS_TESTANSV_H
#define IMPLEMENTATIONS_TESTANSV_H



template<typename Function>
std::tuple<parlay::sequence<long>, parlay::sequence<long>, double> ANSV_generic(Function ANSV, parlay::sequence<long> &A_, long blockSize, bool returnLR=true);

void testArrayShunZhaoAndMineAndBerkman(parlay::sequence<long> A, long blockSize);

int testAllCorrectness();


#endif //IMPLEMENTATIONS_TESTANSV_H
