#include "test.h"

test::test(int i) {
    age = i;
}
test::test() {}

parlay::sequence<long> A (10);

int main2(int argc, char* argv[]) {
    parlay::sequence<long> A (10);
    return A[0];
}
