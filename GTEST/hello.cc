#include <gtest/gtest.h>
#include "../mylib.h"

// Demonstrate some basic assertions.
TEST(FirstTestSuite, CheckingBasicExpects) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);

  EXPECT_EQ(strlen("hello"), 5);

  EXPECT_EQ(returnSquare(5), 25);
}

// First Argument is TestSuite Name, Second is Test Name
TEST(SecondTestSuite, CheckingAssertions) {
  EXPECT_LT(5, 10);
  ASSERT_TRUE(5>1);
}


class QueueTest : public ::testing::Test {
 protected:
  void SetUp() override {
    d1.setData(99); 
    d2.setData(100);
  }

  void TearDown() override {}
  MyLib d1;
  MyLib d2;
};


TEST_F(QueueTest, Test1) {
  EXPECT_EQ(d1.getData(), 99);
  EXPECT_EQ(d2.getData(), 100);
}
