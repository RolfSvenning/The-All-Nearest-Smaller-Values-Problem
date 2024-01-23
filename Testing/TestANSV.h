
#ifndef IMPLEMENTATIONS_TESTANSV_H
#define IMPLEMENTATIONS_TESTANSV_H



std::tuple<parlay::sequence<long>, parlay::sequence<long>, std::string> ANSV_generic(const std::string& algorithmType, parlay::sequence<long> &A_, long blockSize);

std::string ANSV_generic_experiments(const std::string& algorithmType, parlay::sequence<long> &A_, long blockSize);

void testArrayShunZhaoAndMineAndBerkman(parlay::sequence<long> A, long blockSize);

int testAllCorrectness();


#endif //IMPLEMENTATIONS_TESTANSV_H
