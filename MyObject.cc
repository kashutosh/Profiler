#include "MyObject.h"
#include <memory>
using namespace std;

std::unique_ptr<Object> createMyObject(string name, int auxdata) {
    MyObject * o = new MyObject(name, auxdata);
    std::unique_ptr<Object> uptr(o);
    return uptr;
}


