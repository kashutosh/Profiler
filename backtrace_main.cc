#include "backtrace.h"

#include "ObjectStorage.h"
using namespace std;

void f3() {
    std::unique_ptr<Object> bt = createBackTraceObject("trace2");
    /*
    Backtrace *btptr = reinterpret_cast<Backtrace*>(bt.get());
    btptr->trace();
    btptr->translateAddresses();
    */
    // Now add this object to ObjectStorage
    ObjectStorage *os = ObjectStorage::getInstance();
    os->registerForTracking(std::move(bt));
 


}

void f2() {
    std::unique_ptr<Object> bt = createBackTraceObject("trace");
    /*
    Backtrace *btptr = reinterpret_cast<Backtrace*>(bt.get());
    btptr->trace();
    btptr->translateAddresses();
    */
    // Now add this object to ObjectStorage
    ObjectStorage *os = ObjectStorage::getInstance();
    os->registerForTracking(std::move(bt));

    f3();
 
}


void f1() {
    f2();
}

int main() {
    f1();
    ObjectStorage *os = ObjectStorage::getInstance();
    os->print();
}
