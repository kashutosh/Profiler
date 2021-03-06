#ifndef BACKTRACE_H
#define BACKTRACE_H
#include <iostream>
#include <vector>
#include <string>

#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "Object.h"
#include "Exception.h"

#define BT_BUF_SIZE 100


using namespace std;

namespace FlightRecorder {
typedef unsigned int uint;

// Simply said, a backtrace is a Object
class Backtrace : public Object{

private:
    int nptrs;
    void *buffer[BT_BUF_SIZE];
    vector<string> callstack;
    //char **strings;

public:

    Backtrace(string name); 

    ~Backtrace(); 

    bool trace();

    bool translateAddresses(); 

    friend std::unique_ptr<Object> createBackTraceObject(string name);

    bool print();
};


class BackTraceEx : public Exception {
public:
    BackTraceEx (BackTraceEx &e) : Exception (e) {
    }
    BackTraceEx(const char *message) : Exception(message) {

    }
};


std::unique_ptr<Object> createBackTraceObject(string name);
}
#endif
