#ifndef OBJECTSTORAGE_H
#define OBJECTSTORAGE_H

#include <iostream>
#include <vector>
#include <mutex>
#include <memory>
#include "Object.h"

using namespace std;

/*
  One must make sure that the memory allocated by ObjectStorage
  is really well cleaned up.

  Do we need to implement a GC here? Perhaps not.
*/

class ObjectStorage {

private:
    vector<unique_ptr<Object> > objects;

    // Use a lock when mutating objects vector
    std::mutex objectsMutex;
    ObjectStorage();
    static ObjectStorage *object_storage;
    string profilername;
public:
    bool registerForTracking(std::unique_ptr<Object>);
    bool removeFromTracking (const int idToRemove);
    bool print();

    string getProfilerName();
    bool setProfilerName(const string profilername);

    static ObjectStorage *getInstance() {
        if (object_storage == nullptr) {
            object_storage = new ObjectStorage();
        }
        return object_storage;
    } 

    int getObjectsCount();

    bool emptyObjectStorage();

    // override this function to aggregate the data collected.
    bool aggregateData();
};

#endif
