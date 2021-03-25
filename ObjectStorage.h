#include <iostream>
#include <vector>
#include <mutex>          // std::mutex, std::lock

using namespace std;
/*
  This interface represents one data point collected by the profiler
*/

class Object {
    string name;
    double data;
    bool isValid;
public:
    Object(string name, double data) {
        this->name = name;
        this->data = data;
        this->isValid = true;
    }

    string getName  () { return this->name; }
    double getData  () { return this->data;  }
    bool getIsValid () { return this->isValid; }
    void setName  (string name) { this->name = name; }
    void setData  (double data) { this->data = data;  }
    void setIsValid (bool isValid) { this->isValid = isValid; }

private:
    // Disallow creation of objects without parameters
    Object() {}  
};

class ObjectStorage {

private:
    vector<Object *> objects;

    // Use a lock when mutating objects vector
    std::mutex objectsMutex;
    ObjectStorage();
public:
    bool registerForTracking(Object *obj);
    bool removeFromTracking (Object *obj);
};
