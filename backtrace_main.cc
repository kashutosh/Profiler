#include "backtrace.h"

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
