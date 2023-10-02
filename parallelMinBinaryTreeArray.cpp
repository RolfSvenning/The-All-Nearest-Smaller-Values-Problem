//
// Setting number of threads: PARLAY_NUM_THREADS=x
//

#include "parallelMinBinaryTreeArray.h"
#include <iostream>
#include "parlay/io.h"
#include "parlay/primitives.h"
#include "parlay/random.h"
#include "parlay/sequence.h"

bool parallel = true;

parlay::sequence<long> generate_values(long n) {
  parlay::random_generator gen;
  std::uniform_int_distribution<long> dis(0, n-1);

  return parlay::tabulate(2 * n - 1, [&] (long i) {
    if (i <= n - 2) return -1L;
    auto r = gen[i];
    return dis(r);
  });
}

void fixNode(int i, parlay::sequence<long>& A, long n){
  if (i > n - 2) return;
// PARALLEL
  if (parallel){
  parlay::par_do_if(i < n / 1024, // i < 512
          [&]() {fixNode(i * 2 + 1, A, n);},
         [&]() {fixNode(i * 2 + 2, A, n);}
      );
  } else {
  //  SEQUENTIAL
    fixNode(i * 2 + 1, A, n);
    fixNode(i * 2 + 2, A, n);
  }
  A[i] = std::min(A[i * 2 + 1], A[i * 2 + 2]);
}


int main(int argc, char* argv[]){
  auto usage = "Usage: missing 'n' argument. "
               "Creating parallel min binary tree of n elements <n>";
  if (argc != 2){
    std::cout << usage << std::endl;
    return 0;
  }

  long n;
  try { n = std::stol(argv[1]); }
  catch (...) { std::cout << usage << std::endl; return 1; }
  parlay::internal::timer t("Time");


//  std::cout << "1)" << std::endl;
//  std::cout << parlay::to_chars(values) << std::endl;

  parlay::sequence<long> values = generate_values(n);
  t.start();
  fixNode(0, values, n);
  t.next("min binary tree");

//  std::cout << "2)" << std::endl;
//  std::cout << parlay::to_chars(values) << std::endl;
  std::cout << "parallel: " << parallel << std::endl;
}

