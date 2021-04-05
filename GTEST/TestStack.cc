#include <gtest/gtest.h>
#include "../Instrument_Functions/Trace.h"
#include "../Exception.h"
#include <iostream>
using namespace std;
using namespace FlightRecorder;

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
  EXPECT_EQ(s1.numFrames(), 0);
  Dummy d;
  s1.push(d);
  EXPECT_EQ(s1.numFrames(), 1);
  s1.push(d);
  EXPECT_EQ(s1.numFrames(), 2);

}


TEST_F(StackTest, TestOverflow) {
  Dummy d;
  for (int i=0; i<MAX_STACK_DEPTH; i++)
      s1.push(d);
  EXPECT_EQ(s1.numFrames(), MAX_STACK_DEPTH);
  try {
      s1.push(d);
  }
  catch (Exception &e) {
    const char *error = e.what();
    printf("Error is %s \n", error);
    EXPECT_EQ(strcmp(error, "Stack Overflowed beyond capacity"), 0);

  }

}

TEST_F(StackTest, TestUnderflow) {
  Dummy d;
  s1.push(d);
  EXPECT_EQ(s1.numFrames(), 1);
  try {
      Dummy d = s1.pop();
      d = s1.pop();
  }
  catch (Exception &e) {
    const char *error = e.what();
    EXPECT_EQ(strcmp(error, "Stack underflow"), 0);

  }
  catch (std::exception e) {
    printf("Caught std::exception %s\n", e.what());
  }

}
