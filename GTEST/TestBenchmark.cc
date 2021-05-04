#include <gtest/gtest.h>
#include "../Instrument_Functions/hashtable.h"
#include "../Instrument_Functions/Benchmark_Overhead.h"
#include <stdlib.h>
#include <time.h>

#include <iostream>
using namespace std;
using namespace FlightRecorder;

TEST(FirstTestSuite, VoidStarSize) {
  cout << sizeof(void*) << endl;
  cout << sizeof(long long) << endl;
}

TEST(FirstTestSuite, CheckingBasics) {
  //benchmark();
}

