#include "MyObject.h"
#include <memory>
using namespace std;

std::unique_ptr<Object> createMyObject(string name, double data, int auxdata) {
    MyObject * o = new MyObject(name, data, auxdata);
    std::unique_ptr<Object> uptr(o);
    return uptr;
}


