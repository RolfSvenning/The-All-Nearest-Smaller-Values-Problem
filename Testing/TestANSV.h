//
// Created by Rolf Svenning on 18/04/2023.
//

#ifndef IMPLEMENTATIONS_TESTANSV_H
#define IMPLEMENTATIONS_TESTANSV_H


class TestANSV {

};

void testSequential(parlay::sequence<long> A, const long blockSize, bool verbose=false);

void testArrayShunZhaoAndMine(parlay::sequence<long> A, const long blockSize);

void testArrayShunZhaoAndMineAndBerkman(parlay::sequence<long> A, const long blockSize);

int testAllCorrectness();


#endif //IMPLEMENTATIONS_TESTANSV_H
