//
// Created by Rolf Svenning on 18/04/2023.
//

#ifndef IMPLEMENTATIONS_TESTANSV_H
#define IMPLEMENTATIONS_TESTANSV_H


class TestANSV {

};

void testAll(parlay::sequence<long> A, const long blockSize, bool verbose=false);

void testArrayShunZhaoAndMine(parlay::sequence<long> A, const long blockSize);

//std::tuple<std::array<VI, n>, std::array<VI, n>> testShunZhao(std::array<long, n> A);

#endif //IMPLEMENTATIONS_TESTANSV_H
