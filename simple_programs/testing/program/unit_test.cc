#include <limits.h>
#include "prime_count.h"
#include "gtest/gtest.h"

TEST(CountOfPrimeNumbersTest, ForSomeNumbers) {
  EXPECT_EQ(10, GetCountOfPrimeNumbersWithin(20)); 
  EXPECT_EQ(10, GetCountOfPrimeNumbersWithin(22)); 
  EXPECT_GT(GetCountOfPrimeNumbersWithin(24), 11);
  EXPECT_GT(GetCountOfPrimeNumbersWithin(26), 12);
}
