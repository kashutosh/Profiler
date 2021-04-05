#include <gtest/gtest.h>
#include "../ObjectStorage.h"
#include "../Object.h"
#include "../commons.h"

using namespace FlightRecorder;
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

TEST_F(ObjectStorageTest, Test2) {
  ObjectStorage *os1 = ObjectStorage::getInstance();
  EXPECT_NE(os1, nullptr);
  ObjectStorage *os2 = ObjectStorage::getInstance();
  EXPECT_NE(os2, nullptr);
  ASSERT_EQ(os1, os2);
}


TEST_F(ObjectStorageTest, Test3) {
  ObjectStorage *os = ObjectStorage::getInstance();
  EXPECT_NE(os, nullptr);
  std::unique_ptr<Object> ptr1(createObject("object2"));
  os->registerForTracking(std::move(ptr1));
  ASSERT_EQ(ptr1, nullptr);
  int numObjects = os->getObjectsCount();
  ASSERT_EQ(numObjects, 1);

  std::unique_ptr<Object> ptr2(createObject("object2"));
  os->registerForTracking(std::move(ptr2));
  numObjects = os->getObjectsCount();
  ASSERT_EQ(numObjects, 2);

  os->emptyObjectStorage();
  numObjects = os->getObjectsCount();
  ASSERT_EQ(numObjects, 0);


}
