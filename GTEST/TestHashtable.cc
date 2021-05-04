#include <gtest/gtest.h>
#include "../Instrument_Functions/hashtable.h"
#include <stdlib.h>
#include <time.h>

#include <iostream>
using namespace std;
using namespace FlightRecorder;
TEST(FirstTestSuite, CheckingBasics) {

  Hashtable h;

  h.initializeBuckets();
  int idx;
  uint key;
  key = 10;
  idx = h.insert(key);
  ASSERT_EQ(idx, 0);
  
  key = 72;
  idx = h.insert(key);
  ASSERT_EQ(idx, 1);

  key = 72;
  idx = h.insert(key);
  ASSERT_EQ(idx, 1);

  h.destroyHashtable();
}


TEST(FirstTestSuite, DestroyHashtable) {

  Hashtable h;
  h.initializeBuckets();
  int idx;
  uint key;
  key = 1;
  idx = h.insert(key);
  ASSERT_EQ(idx, 0);
  
  key = 72;
  idx = h.insert(key);
  ASSERT_EQ(idx, 1);

  key = 142;
  idx = h.insert(key);
  ASSERT_EQ(idx, 2);


  key = 21;
  idx = h.insert(key);
  ASSERT_EQ(idx, 3);

  printf("Number of keys stored %d\n", h.getNumKeysStored());
  h.destroyHashtable();

  
}

TEST(FirstTestSuite, CheckingBasics2) {

  Hashtable h;
  h.initializeBuckets();
  int idx1, idx2;
  int key1, key2;
  key1 = 1; key2 = 72;
  idx1 = h.insert(key1);
  idx2 = h.insert(key2);
  ASSERT_GE(idx1, 0);
  ASSERT_GE(idx2, 0);
  ASSERT_NE(idx1, idx2);

  int findIdx1 = h.find(key1);  
  ASSERT_EQ(findIdx1, idx1);
  int findIdx2 = h.find(key2);  
  ASSERT_EQ(findIdx2, idx2);
  h.destroyHashtable();
}

TEST(FirstTestSuite, CheckHashFunction) {

  Hashtable h;
  h.initializeBuckets();

  for (int i=0; i<143; i++) {
    int hashval = h.hash(i);
    ASSERT_GE(hashval, 0);
    ASSERT_LE(hashval, 70);
  }
  for (int i=0; i>-143; i--) {
    int hashval = h.hash(i);
    ASSERT_GE(hashval, 0);
    ASSERT_LE(hashval, 70);
  }

  h.destroyHashtable();
}

TEST(FirstTestSuite, CheckHashFunction2) {

  Hashtable h;
  h.initializeBuckets();

  for (int i=0; i<143; i++) {
    int hashval = h.hash(i);
    ASSERT_GE(hashval, 0);
    ASSERT_LE(hashval, 70);
  }
  for (int i=0; i>-143; i--) {
    int hashval = h.hash(i);
    ASSERT_GE(hashval, 0);
    ASSERT_LE(hashval, 70);
  }

}
TEST(FirstTestSuite, CheckInitialization) {

  Hashtable h;
  h.initializeBuckets();

  for (int i=0; i<NUM_BUCKETS_PRIME; i++) {
    Hashtable::Bucket *bucket = h.getBucket(i);
    ASSERT_EQ(bucket->chain, (void*)NULL);
  }
  h.destroyHashtable();

}
TEST(FirstTestSuite, InsertAndRetrieve) {

  Hashtable h;
  h.initializeBuckets();
  int idx1, idx2;
  int key1;
  key1 = 21; 
  idx1 = h.insert(key1);
  idx2 = h.insert(21);
  //h.printHashTable();  
  ASSERT_EQ(idx1, idx2);

//  idx1 = h.insert(key1);
  idx2 = h.find(key1);
  ASSERT_EQ(idx1, idx2);
}

TEST(FirstTestSuite, InsertTwoIdentical) {

  Hashtable h;
  h.initializeBuckets();
  int idx1, idx2;
  int key1;
  key1 = 92; 
  idx1 = h.insert(key1);
  idx2 = h.insert(21);
  ASSERT_NE(idx1, idx2);

  idx2 = h.find(key1);
  ASSERT_EQ(idx1, idx2);

  key1 = 1;
  idx1 = h.insert(key1);
  idx2 = h.find(key1);
  ASSERT_EQ(idx1, idx2);
  h.printHashTable();  
  h.destroyHashtable();
}

TEST(FirstTestSuite, InsertSeveralIdenticalHashes) {

  Hashtable h;
  h.initializeBuckets();
  int idx1, idx2;
  srand(time(NULL));
  int key1 = rand()%100;
  for (int i=0; i<100;i++)
  {
  key1 = key1+NUM_BUCKETS_PRIME; 
  idx1 = h.insert(key1);
  idx2 = h.find(key1);
  ASSERT_EQ(idx1, idx2);
  }

  h.destroyHashtable();
}

TEST(FirstTestSuite, TestRandomHashes) {

  Hashtable h;
  h.initializeBuckets();
  int idx1, idx2;
  srand(time(NULL));
  for (int i=0; i<100;i++)
  {
  int key1 = rand()%10000;
  idx1 = h.insert(key1);
  idx2 = h.find(key1);
  ASSERT_EQ(idx1, idx2);
  }

  h.destroyHashtable();
}

