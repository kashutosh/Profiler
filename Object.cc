#include "ObjectStorage.h"
#include <memory>
using namespace std;


// Question is how to call this function?
// Should we make this static
// Or should we make it a friend function?
std::unique_ptr<Object> createObject(string name, double data) {
    Object * o = new Object();
    o->name = name;
    o->data = data;
    o->isValid = true;
    std::unique_ptr<Object> uptr(o);
    return uptr;
}


std::unique_ptr<Object> createObject() {
    Object * o = new Object();
    o->name = "";
    o->data = 0;
    o->isValid = true;
    std::unique_ptr<Object> uptr(o);
    return uptr;
}
