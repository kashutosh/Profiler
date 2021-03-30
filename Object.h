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


class Object {
    int id;
    string name;
    double data;
    bool isValid;

private:
    // Forbid this constructor by making it private
    // Objects must be created by createObject methods
    Object() = delete;

protected:
    Object(string name, double data) {
        cout << "Creating object with data " << data << endl;
        this->name = name;
        this->data = data;
        this->isValid = true;
    }

public:
    // Derive the objects to be stored using Object class.
    // Therefore the destructor must be virtual
    virtual ~Object();
    int getId       () { return this->id; }
    string getName  () { return this->name; }
    double getData  () { return this->data;  }
    bool getIsValid () { return this->isValid; }
    void setId    (int id) { this->id = id; }
    void setName  (string name) { this->name = name; }
    void setData  (double data) { this->data = data;  }
    void setIsValid (bool isValid) { this->isValid = isValid; }

    // When we say unique_ptr, we are effectively saying that I'll take 
    //    the ownership. The guy who created this object will no more 
    //    be able to modify it. This is an excellent implementation if 
    //    we are to handle non-mutable objects.
    friend std::unique_ptr<Object> createObject(string name, double data);

   // Disallow creation of objects without parameters
    std::unique_ptr<Object> createObject() = delete;
};



#endif
