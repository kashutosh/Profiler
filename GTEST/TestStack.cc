#include <gtest/gtest.h>
#include "../Instrument_Functions/Trace.h"
int initialization_complete = 1;
// Demonstrate some basic assertions.
TEST(FirstTestSuite, CheckingBasicExpects) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);

  EXPECT_EQ(strlen("hello"), 5);

}



class StackTest : public ::testing::Test {
 protected:
  void SetUp() override {
  }

  void TearDown() override {}
  Stack s1;
};


TEST_F(StackTest, Test1) {
  EXPECT_NE(s1.numFrames(), 11);
  EXPECT_EQ(s1.numFrames(), -1);
  Dummy d;
  s1.push(d);
  EXPECT_EQ(s1.numFrames(), 0);
  s1.push(d);
  EXPECT_EQ(s1.numFrames(), 0);

}
