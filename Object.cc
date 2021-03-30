#include "ObjectStorage.h"
#include <memory>
using namespace std;

Object::~Object() {
    cout << "Deleting object with id: " << id << " and data " << data << endl;
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

// If we want to force an API that constructs an object of a class be returned 
// as unique_ptr
// whose objects we do not want to construct publicly
// then we are forced to make constructor private
// But that means we cannot inherit from that class
// So the constructor must be protected
// This is very awful looking coding, isn't it?



