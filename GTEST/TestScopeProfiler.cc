#include <gtest/gtest.h>
#include "../scope.h"
#include "../Exception.h"
#include <iostream>
using namespace std;

TEST(FirstTestSuite, CheckingBasicUsage) {
  int hitException = 0;
  try {
    SCOPE_TIMER(1, "scope1");
    hitException = 0;
  }
  catch (std::exception &e){
    hitException = 1;
  }

  // If we hit any exception, then surely this 
  // variable is not 0
  ASSERT_EQ(hitException, 0);
}

TEST(FirstTestSuite, CheckingObjectsCount) {
  // Make sure that you have
  // nothing in the objects store

  // Otherwise all your profiling work is useless
  ObjectStorage *os = ObjectStorage::getInstance();
  os->emptyObjectStorage();
  {
    SCOPE_TIMER(1, "scope1");
  }
  int count = os->getObjectsCount();
  ASSERT_EQ(count, 1);

}


