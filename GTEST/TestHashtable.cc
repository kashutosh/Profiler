#include <gtest/gtest.h>
#include "../Instrument_Functions/hashtable.h"
#include <stdlib.h>
#include <time.h>

#include <iostream>
using namespace std;
using namespace FlightRecorder;
TEST(FirstTestSuite, CheckingBasics) {


  FlightRecorder::initializeBuckets();
  int idx;
  uint key;
  key = 10;
  idx = FlightRecorder::insert(key);
  ASSERT_EQ(idx, key%71);
  
  key = 72;
  idx = FlightRecorder::insert(key);
  ASSERT_EQ(idx, key%71);

  key = 72;
  idx = FlightRecorder::insert(key);
  ASSERT_EQ(idx, key%71);

  FlightRecorder::destroyHashtable();
}

TEST(FirstTestSuite, DestroyHashtable) {

  FlightRecorder::initializeBuckets();
  int idx;
  uint key;
  key = 1;
  idx = FlightRecorder::insert(key);
  ASSERT_EQ(idx, key%71);
  
  key = 72;
  idx = FlightRecorder::insert(key);
  ASSERT_EQ(idx, key%71);

  key = 142;
  idx = FlightRecorder::insert(key);
  ASSERT_EQ(idx, key%71);


  key = 21;
  idx = FlightRecorder::insert(key);
  ASSERT_EQ(idx, key%71);

  printf("Number of keys stored %d\n", FlightRecorder::getNumKeysStored());
  FlightRecorder::destroyHashtable();

  
}


TEST(FirstTestSuite, CheckingBasics2) {

  FlightRecorder::initializeBuckets();
  int idx1, idx2;
  int key1, key2;
  key1 = 1; key2 = 72;
//  idx1 = FlightRecorder::insert(key1);
//  idx2 = FlightRecorder::insert(key2);
//  ASSERT_EQ(idx1, idx2);

//  int findIdx1 = FlightRecorder::find(key1);  
//  ASSERT_EQ(findIdx1, idx1);
//  int findIdx2 = FlightRecorder::find(key2);  
//  ASSERT_EQ(findIdx2, idx2);
}


TEST(FirstTestSuite, CheckHashFunction) {

  FlightRecorder::initializeBuckets();

  for (int i=0; i<143; i++) {
    int hashval = FlightRecorder::hash(i);
    ASSERT_GE(hashval, 0);
    ASSERT_LE(hashval, 70);
  }
  for (int i=0; i>-143; i--) {
    int hashval = FlightRecorder::hash(i);
    ASSERT_GE(hashval, 0);
    ASSERT_LE(hashval, 70);
  }

  FlightRecorder::destroyHashtable();
}


TEST(FirstTestSuite, CheckHashFunction2) {

  FlightRecorder::initializeBuckets();

  for (int i=0; i<143; i++) {
    int hashval = FlightRecorder::hash(i);
    ASSERT_GE(hashval, 0);
    ASSERT_LE(hashval, 70);
  }
  for (int i=0; i>-143; i--) {
    int hashval = FlightRecorder::hash(i);
    ASSERT_GE(hashval, 0);
    ASSERT_LE(hashval, 70);
  }

}

TEST(FirstTestSuite, CheckInitialization) {

  FlightRecorder::initializeBuckets();

  for (int i=0; i<NUM_THREADS_PRIME; i++) {
    Bucket *bucket = getBucket(i);
    ASSERT_EQ(bucket->chain, (void*)NULL);
  }
  FlightRecorder::destroyHashtable();

}

TEST(FirstTestSuite, InsertAndRetrieve) {

  FlightRecorder::initializeBuckets();
  int idx1, idx2;
  int key1;
  key1 = 21; 
  idx1 = FlightRecorder::insert(key1);
  idx2 = FlightRecorder::insert(21);
  //FlightRecorder::printHashTable();  
  ASSERT_EQ(idx1, idx2);

//  idx1 = FlightRecorder::insert(key1);
  idx2 = FlightRecorder::find(key1);
  ASSERT_EQ(idx1, idx2);
}

TEST(FirstTestSuite, InsertTwoIdentical) {

  FlightRecorder::initializeBuckets();
  int idx1, idx2;
  int key1;
  key1 = 92; 
  idx1 = FlightRecorder::insert(key1);
  idx2 = FlightRecorder::insert(21);
  ASSERT_EQ(idx1, idx2);

  idx2 = FlightRecorder::find(key1);
  ASSERT_EQ(idx1, idx2);

  key1 = 1;
  idx1 = FlightRecorder::insert(key1);
  idx2 = FlightRecorder::find(key1);
  ASSERT_EQ(idx1, idx2);
  FlightRecorder::printHashTable();  
  FlightRecorder::destroyHashtable();
}


TEST(FirstTestSuite, InsertSeveralIdenticalHashes) {

  FlightRecorder::initializeBuckets();
  int idx1, idx2;
  srand(time(NULL));
  int key1 = rand()%100;
  for (int i=0; i<100;i++)
  {
  key1 = key1+NUM_THREADS_PRIME; 
  idx1 = FlightRecorder::insert(key1);
  idx2 = FlightRecorder::find(key1);
  ASSERT_EQ(idx1, idx2);
  }

  FlightRecorder::destroyHashtable();
}

TEST(FirstTestSuite, TestRandomHashes) {

  FlightRecorder::initializeBuckets();
  int idx1, idx2;
  srand(time(NULL));
  for (int i=0; i<100;i++)
  {
  int key1 = rand()%10000;
  idx1 = FlightRecorder::insert(key1);
  idx2 = FlightRecorder::find(key1);
  ASSERT_EQ(idx1, idx2);
  }

  FlightRecorder::destroyHashtable();
}
