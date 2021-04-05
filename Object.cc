#include "ObjectStorage.h"
#include <memory>
using namespace std;

namespace FlightRecorder {
Object::~Object() {
    cout << "Deleting object with name: " << id << endl;
}

// Question is how to call this function?
// Should we make this static
// Or should we make it a friend function?
std::unique_ptr<Object> createObject(const string name) {
    try {
        Object * o = new Object(name);
        o->isValid = true;
        std::unique_ptr<Object> uptr(o);
        return uptr;
    }
    catch (exception &e) {
        throw;
    }
}

// If we want to force an API that constructs an object of a class be returned 
// as unique_ptr
// whose objects we do not want to construct publicly
// then we are forced to make constructor private
// But that means we cannot inherit from that class
// So the constructor must be protected
// This is very awful looking coding, isn't it?


}
