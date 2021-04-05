#include "backtrace.h"
#include "ObjectStorage.h"

using namespace std;


namespace FlightRecorder {
std::unique_ptr<Object> createBackTraceObject(string name) {

    Backtrace *bt = new Backtrace(name);
    bt->trace();
    try {
        bt->translateAddresses();
    }
    catch (BackTraceEx &e) {
        cout << "Caught an exception in createBackTraceObject " << e.what() << endl;
    }
    std::unique_ptr<Object> optr (bt);
    return optr;
}

Backtrace::Backtrace(string name) : 
    Object(name) { 
}


Backtrace::~Backtrace() {
}
// This file provides functions for taking backtraces
// Backtrace objects can be stored in ObjectsStorage

bool Backtrace::trace() {
    // Collect the backtrace in this->buffer
    this->nptrs = backtrace(this->buffer, BT_BUF_SIZE);
    return true;
}

bool Backtrace::translateAddresses() {
    char **strings;
    strings = backtrace_symbols(this->buffer, this->nptrs);
    if (strings == NULL) {
        //perror("backtrace_symbols");
        //exit(EXIT_FAILURE);
        BackTraceEx e("Unable to get backtrace in string form");
        throw e;
    }


    // Copy the strings to Backtrace object
    for (int j = 0; j < nptrs; j++) {
        //printf("%s\n", strings[j]);
        string s(strings[j]);
        // Copy by value
        // Let this string object get destroyed after the loop
        this->callstack.push_back(s);
    }


    // Free the memory allocated to strings
    free(strings);
    return true;
}



bool Backtrace::print() {
    for (vector<string>::const_iterator it = callstack.begin();
         it!=callstack.end(); it++) {
        cout << *it << endl;
    }
    return true;
}
}

