#include <gtest/gtest.h>
#include "../ObjectStorage.h"

//ObjectStorage *ObjectStorage ::object_storage = nullptr;

class ObjectStorageTest : public ::testing::Test {
 protected:
  void SetUp() override {
  }

  void TearDown() override {}
};


TEST_F(ObjectStorageTest, Test1) {
  ObjectStorage *os = ObjectStorage::getInstance();
  EXPECT_NE(os, nullptr);
}
