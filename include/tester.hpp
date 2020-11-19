// Copyright 2018 Your Name <your_email>

#ifndef INCLUDE_TESTER_HPP_
#define INCLUDE_TESTER_HPP_

//#include  <cstdint>
#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>

class Tester {
 public:
  explicit Tester(std::vector<int> series);
  ~Tester();
  int* get_random_array(int size);
  int random_16(int zero, int array_size);
  void free_array(int* array);
  double direct(int array_size);
  double reverse(int array_size);
  double randomn(int array_size);
  void experiment(std::ostream& out = std::cout);

 private:
  std::vector<int> m_series;
  const int iter = 1000;
  const int step = 16;
  int L1_size;
  int tmp;
  int count = 0;
};
#endif // INCLUDE_TESTER_HPP_
