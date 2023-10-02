//
// Setting number of threads: PARLAY_NUM_THREADS=x
//

#include <iostream>

#include "parlay/io.h"
#include <parlay/primitives.h>
#include <parlay/random.h>
#include <parlay/sequence.h>

bool parallel = true;

// if left_i (right_i) is equal to -1 it means that it has no left (right) child
struct node {
  long val;
  long minVal;
  struct node * left_i;
  struct node * right_i;
  struct node * parent;
};

parlay::sequence<node> generate_values(long n) {
  parlay::random_generator gen;
  std::uniform_int_distribution<long> dis(0, n-1);

  return parlay::tabulate(n, [&] (long i) {
    auto r = gen[i];
    return node{dis(r), 999, nullptr, nullptr, nullptr};
  });
}



// start: first index with an element
// end: last index with an element
long fixNode2(parlay::sequence<node>& A, long start, long end) {
  long mid_i = (start + end) / 2;
  if (end < start) return -1;
  long rootLeft_i = fixNode2(A, start, mid_i - 1);
  long rootRight_i = fixNode2(A, mid_i + 1, end);
  node & mid = A[mid_i];
  

  node & left = A[rootLeft_i];
  node & right = A[rootRight_i];

  long leftMinVal;
  if (rootLeft_i != -1) {
    leftMinVal = left.minVal;
    mid.left_i = &left;
    left.parent = &mid;
  } else {
    leftMinVal = A.size();
  }

  long rightMinVal;
  if (rootRight_i != -1) {
    rightMinVal = right.minVal;
    mid.right_i = &right;
    right.parent = &mid;
  } else {
    rightMinVal = A.size();
  }

  mid.minVal = std::min(mid.val, std::min(leftMinVal, rightMinVal));
//  std::cout << "values: " << " " << left.minVal << " " << mid.minVal << " "  << right.minVal << std::endl;
  return mid_i;
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


  parlay::sequence<node> values = generate_values(n);

//  std::cout << "1) input" << std::endl;
//  std::cout << parlay::to_chars(parlay::tabulate(n, [&] (long i) {
//    return values[i].val;
//  })) << std::endl;


  t.start();
  fixNode2(values, 0, n - 1);
  t.next("min binary tree");

//  std::cout << "2)" << std::endl;
//  std::cout << parlay::to_chars(parlay::tabulate(n, [&] (long i) {
//    return values[i].minVal;
//  })) << std::endl;



  std::cout << "parallel: " << parallel << std::endl;
}

