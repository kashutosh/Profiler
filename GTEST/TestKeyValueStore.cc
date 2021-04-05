#include <gtest/gtest.h>
#include "../KeyValueStore.h"
#include <iostream>
using namespace std;
using namespace FlightRecorder;


TEST(FirstTestSuite, CheckingBasics) {

  KeyValueStore *kvs = KeyValueStore::getInstance();
  int numkeys = kvs->getObjectsCount();
  ASSERT_EQ(numkeys, 0);

  string nextname = kvs->getUniqueName();
  ASSERT_EQ(nextname, "unique1");
  nextname = kvs->getUniqueName();
  ASSERT_EQ(nextname, "unique2");
  cout << nextname << endl;

}


TEST(FirstTestSuite, CheckingDuplicates) {
  KeyValueStore *kvs = KeyValueStore::getInstance();
  bool result = kvs->insertKeyValue("key1", "value1");
  ASSERT_EQ(result, true);
  result = kvs->insertKeyValue("key1", "value1");
  ASSERT_EQ(result, false);
}


TEST(FirstTestSuite, CheckingValues) {
  KeyValueStore *kvs = KeyValueStore::getInstance();
  bool result = kvs->insertKeyValue("key2", "value2");
  ASSERT_EQ(result, true);
  string val = kvs->getValue("key2");
  ASSERT_EQ(val, "value2");
}

