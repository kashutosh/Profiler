#ifndef SCOPE_H
#define SCOPE_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "ObjectStorage.h"
using namespace std;

namespace FlightRecorder {
class Record {
typedef unsigned long long hrtime;

__inline__ unsigned long long gethrtime(void)
{
  unsigned hi, lo;
  __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
  return ( (unsigned long long)lo)|( ((unsigned long long)hi)<<32 );
}

public:
    string name;
    hrtime start_timestamp;
    hrtime end_timestamp;
    static int internal_level;
    Record(string _name); 
    ~Record(); 
private:
    Record() {}

};



#define SCOPE_TIMER(number, name) Record r##number(name)
}

#endif
