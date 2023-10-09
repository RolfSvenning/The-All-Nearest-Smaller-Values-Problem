//
// Setting number of threads: PARLAY_NUM_THREADS=x
//

#include <iostream>
#include "parlay/sequence.h"
#include "parlay/primitives.h"

bool parallel = true;

parlay::sequence<long> generate_values(long n) {
  parlay::random_generator gen(0);
  std::uniform_int_distribution<long> dis(0, n-1);

  return parlay::tabulate(2 * n - 1, [&] (long i) {
    if (i <= n - 2) return -1L;
    auto r = gen[i];
    return dis(r);
  });
}

parlay::sequence<long> delayed_generate_values(long n) {
  parlay::random_generator gen(0);
  std::uniform_int_distribution<long> dis(0, n-1);

  return parlay::tabulate(2 * n - 1, [&] (long i) {
    if (i <= n - 2) return -1L;
    auto r = gen[i];
    return dis(r);
  });
}

int main(int argc, char* argv[]) {
  auto usage = "Usage: missing 'n' argument. "
               "Comparing parallel and sequential loops <n>";
  if (argc != 2) {
    std::cout << usage << std::endl;
    return 0;
  }

  long n;
  try {
    n = std::stol(argv[1]);
  } catch (...) {
    std::cout << usage << std::endl;
    return 1;
  }
  parlay::internal::timer t("Time");
  parlay::sequence<long> A1 = generate_values(n);

  // SEQUENTIAL
  std::cout << " --- SEQ ---" << std::endl;
  t.start();
  for (int i = 0; i < A1.size(); ++i) {
    A1[i] += 1;
  }
  t.next("for loop");
  long s1 = std::reduce(A1.begin(), A1.end());
  t.next("std::reduce");

  // PARALLEL
  std::cout << "\n --- PAR ---" << std::endl;
  parlay::sequence<long> A2 = generate_values(n);
  t.start();
  parlay::parallel_for (0, A2.size(), [&] (size_t i) {
        A2[i] += 1;
      });
  t.next("for loop");
  long s2 = parlay::reduce(A2);
  t.next("reduce (sum)");

  return s1 + s2;
}










