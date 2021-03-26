#include "ObjectStorage.h"
#include <memory>
using namespace std;

Object::~Object() {
    cout << "Deleting object with data " << data << endl;
}

// Question is how to call this function?
// Should we make this static
// Or should we make it a friend function?
std::unique_ptr<Object> createObject(string name, double data) {
    Object * o = new Object(name, data);
    o->isValid = true;
    std::unique_ptr<Object> uptr(o);
    return uptr;
}



