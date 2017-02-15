#include <limits.h>
// #include "prime_count.h"
#include "gtest/gtest.h"

extern "C" {
       	int GetPrimeNumbers(int);
}

TEST(CountOfPrimeNumbersTest, ForSomeNumbers) {
  EXPECT_EQ(10, GetPrimeNumbers(20)); 
  EXPECT_EQ(10, GetPrimeNumbers(22)); 
  EXPECT_GT(GetPrimeNumbers(24), 11);
  EXPECT_GT(GetPrimeNumbers(26), 12);
}
