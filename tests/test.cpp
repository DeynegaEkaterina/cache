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

  Tester tester(cache.L1, cache.L3);
  tester.define_series();
  tester.experiment();
  EXPECT_TRUE(true);
}
