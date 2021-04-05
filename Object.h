#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <vector>
#include <mutex>
#include <memory>

using namespace std;
/*
  This interface represents one data point collected by the profiler
*/

namespace FlightRecorder {
class Object {
    int id;
    string name;
    bool isValid;

private:
    // Forbid this constructor by making it private
    // Objects must be created by createObject methods
    Object() = delete;

protected:
    Object(string name): name(name) {
        this->isValid = true;
    }

public:
    // Derive the objects to be stored using Object class.
    // Therefore the destructor must be virtual
    virtual ~Object();
    int getId       () { return this->id; }
    string getName  () { return this->name; }
    bool getIsValid () { return this->isValid; }
    void setId    (int id) { this->id = id; }
    void setName  (string name) { this->name = name; }
    void setIsValid (bool isValid) { this->isValid = isValid; }

    virtual bool print() {return true; };

    // When we say unique_ptr, we are effectively saying that I'll take 
    //    the ownership. The guy who created this object will no more 
    //    be able to modify it. This is an excellent implementation if 
    //    we are to handle non-mutable objects.
    friend std::unique_ptr<Object> createObject(const string name);

   // Disallow creation of objects without parameters
    std::unique_ptr<Object> createObject() = delete;
};

}

#endif
