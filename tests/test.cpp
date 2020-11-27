// Copyright 2018 Your Name <your_email>
#include "tester.hpp"
#include <gtest/gtest.h>



TEST(Example, EmptyTest) {
  EXPECT_TRUE(true);
}

TEST(Ex, EmptyTest) {
  struct Cache{
    int L1 = 96;
    int L3 = 24576;
  };
  Cache cache;
  std::vector<int> series;
  
  double start = cache.L1 * 0.5*1024/sizeof(int);
  double end = cache.L3 * 1.5*1024/sizeof(int);
  while (start < end){
    series.push_back(start);
    start = start*2;
  }
  series.push_back(end);
  Tester tester(series);
  tester.experiment();
  EXPECT_TRUE(true);
}
