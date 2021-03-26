#ifndef OBJECTSTORAGE_H
#define OBJECTSTORAGE_H

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
    /*{
        cout << "Creating object with data " << data << endl;
        this->name = "";
        this->data = 0;
        this->isValid = true;
    } */ 
 
    Object(string name, double data) {
        cout << "Creating object with data " << data << endl;
        this->name = name;
        this->data = data;
        this->isValid = true;
    }

public:

    ~Object();
    int getId       () { return this->id; }
    string getName  () { return this->name; }
    double getData  () { return this->data;  }
    bool getIsValid () { return this->isValid; }
    void setId    (int id) { this->id = id; }
    void setName  (string name) { this->name = name; }
    void setData  (double data) { this->data = data;  }
    void setIsValid (bool isValid) { this->isValid = isValid; }

    friend std::unique_ptr<Object> createObject(string name, double data);
    std::unique_ptr<Object> createObject() = delete;
   // Disallow creation of objects without parameters
};


class ObjectStorage {

private:
    vector<unique_ptr<Object> > objects;

    // Use a lock when mutating objects vector
    std::mutex objectsMutex;
public:
    ObjectStorage();
    bool registerForTracking(std::unique_ptr<Object>);
    bool removeFromTracking (Object *obj);
    bool print();

    static ObjectStorage *object_storage;
    static ObjectStorage *getInstance() {
        if (object_storage == nullptr) {
            object_storage = new ObjectStorage();
        }
        return object_storage;
    } 

    bool emptyObjectStorage();
};

#endif
