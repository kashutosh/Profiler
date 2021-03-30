#include "backtrace.h"


std::unique_ptr<Object> createBackTraceObject(string name) {

    Backtrace *bt = new Backtrace(name);
    bt->trace();
    bt->translateAddresses();
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
       perror("backtrace_symbols");
       exit(EXIT_FAILURE);
   }

   for (int j = 0; j < nptrs; j++)
       printf("%s\n", strings[j]);

   free(strings);
   return true;
}

void f2() {
    std::unique_ptr<Object> bt = createBackTraceObject("trace");
    /*
    Backtrace *btptr = reinterpret_cast<Backtrace*>(bt.get());
    btptr->trace();
    btptr->translateAddresses();
    */
    // Now add this object to ObjectStorage
}



void f1() {
    f2();
}

int main() {
    f1();
}
