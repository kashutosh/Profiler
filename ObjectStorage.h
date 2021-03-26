#ifndef OBJECTSTORAGE_H
#define OBJECTSTORAGE_H

#include <iostream>
#include <vector>
#include <mutex>
#include <memory>
#include "Object.h"

using namespace std;


class ObjectStorage {

private:
    vector<unique_ptr<Object> > objects;

    // Use a lock when mutating objects vector
    std::mutex objectsMutex;
    ObjectStorage();
    static ObjectStorage *object_storage;
public:
    bool registerForTracking(std::unique_ptr<Object>);
    bool removeFromTracking (int idToRemove);
    bool print();

    static ObjectStorage *getInstance() {
        if (object_storage == nullptr) {
            object_storage = new ObjectStorage();
        }
        return object_storage;
    } 

    bool emptyObjectStorage();
};

#endif
