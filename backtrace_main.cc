#include "backtrace.h"

#include "ObjectStorage.h"
using namespace std;
using namespace FlightRecorder;

void f3() {
    std::unique_ptr<Object> bt = createBackTraceObject("trace2");
    ObjectStorage *os = ObjectStorage::getInstance();
    os->registerForTracking(std::move(bt));
}

void f2() {
    std::unique_ptr<Object> bt = createBackTraceObject("trace");
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
