#include <gtest/gtest.h>
#include "../Instrument_Functions/LinkedListOfFrames.h"
#include "../Instrument_Functions/FunctionTracer.h"
#include "../Instrument_Functions/hashtable.h"
#include <stdlib.h>
#include <time.h>

#include <iostream>
using namespace std;
using namespace FlightRecorder;

TEST(FirstTestSuite, CheckingInitialization) {

  FlightRecorder::initializeLinkedLists();
  for (int i=0; i<NUM_BUCKETS_PRIME; i++) {
    FrameInformation * f = FlightRecorder::getFrame(i);
    ASSERT_EQ(f->next, (void*) NULL);
  }
  
}


TEST(FirstTestSuite, CheckingInitialization2) {

  FlightRecorder::initializeLinkedLists();
  for (int i=0; i<NUM_BUCKETS_PRIME; i++) {
    FrameInformation * f = FlightRecorder::getFrame(i);
    FrameInformation * f_tail = FlightRecorder::getTail(i);
    ASSERT_EQ(f, f_tail);
  }
  
}


TEST(FirstTestSuite, CheckAppendNodeToTail) {

  FlightRecorder::initializeLinkedLists();
  srand(time(NULL));
  int counter = 99;

  for (int i=0;i<100; i++) {
    int index = rand()%NUM_BUCKETS_PRIME;
    FrameInformation f;
    f.id = counter++;
    bool result = FlightRecorder::appendNodeToTailOfAList(&f, index);
    ASSERT_EQ(result, true);

    FrameInformation *fr = FlightRecorder::getTail(index);
    ASSERT_EQ(f.id, fr->id);
  }
  
}


void foo() {

}

TEST(FirstTestSuite, CheckAppendNodeToTail2) {

  FlightRecorder::initializeLinkedLists();
  int counter = 99;

  FunctionTracer::initializeTracer();
  int index = counter%NUM_BUCKETS_PRIME;
  FrameInformation f;
  f.id = counter;
  f.operation = PUSH;
  f.address = (void*)&foo;


  printf("Appending to list number %d\n", index);
  bool result = FlightRecorder::appendNodeToTailOfAList(&f, index);
  ASSERT_EQ(result, true);


  FrameInformation *fr = FlightRecorder::getTail(index);
  ASSERT_EQ(fr, &f);
  ASSERT_EQ(f.id, fr->id);
  printf ("Pushed node's address is %p\n", &f);

  FrameInformation fpop1;
  fpop1.operation = POP;
  fpop1.id = 100;
  result = FlightRecorder::appendNodeToTailOfAList(&fpop1, index);
  ASSERT_EQ(result, true);

  fr = FlightRecorder::getTail(index);
  ASSERT_EQ(fr, &fpop1);


  FrameInformation fpop2;
  fpop2.operation = POP;
  fpop2.id = 101;
  result = FlightRecorder::appendNodeToTailOfAList(&fpop2, index);
  ASSERT_EQ(result, true);

  fr = FlightRecorder::getTail(index);
  ASSERT_EQ(fr, &fpop2);

  {
  index = 21;
  FrameInformation fpop2;
  fpop2.operation = POP;
  fpop2.id = 111111;
  result = FlightRecorder::appendNodeToTailOfAList(&fpop2, index);
  ASSERT_EQ(result, true);

  fr = FlightRecorder::getTail(index);
  ASSERT_EQ(fr, &fpop2);


  }


  FunctionTracer::stopTracer(nullptr);

}


/**
TEST(FirstTestSuite, GenerateStrings) {

  char strings[26*26][3];
  int ctr1 = -1;
  for (char ch1='a'; ch1<='z'; ch1++) {
    ctr1++;
    int ctr2 = -1;
    for (char ch2='a'; ch2<='z'; ch2++) {
      ctr2++;
//      printf("%c%c\t", ch1,ch2);
      strings[ctr1*ctr2 + ctr2][0] = ch1;
      strings[ctr1*ctr2 + ctr2][1] = ch2;
      strings[ctr1*ctr2 + ctr2][2] = '\0';
      printf("%s\t", strings[ctr1*ctr2+ctr2]);
    }
  }

  
}
**/
