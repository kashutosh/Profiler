#include "ObjectStorage.h"
#include <mutex>

using namespace std;

// For sake of creating singletons
ObjectStorage *ObjectStorage ::object_storage = nullptr;


ObjectStorage::ObjectStorage() {
    cout << "Calling constructor of ObjectStorage " << endl;
}

bool ObjectStorage::registerForTracking(std::unique_ptr<Object> obj) {
    // Lock the objects vector
    objectsMutex.lock();
    objects.push_back(obj.get());
    objectsMutex.unlock();
    return true;
}

bool ObjectStorage::removeFromTracking(Object *obj) {
    // identify in the vector where this object is stored
    // mark isValid = false


    // Caution: objects is mutating in code below
    for (vector<Object *>::iterator it = objects.begin();
         it!= objects.end(); it++) {
        Object *current = *it;
        if (obj->getName() == current->getName()) {
            objectsMutex.lock();
            current->setIsValid (false);
            objectsMutex.unlock();
        }
    }
    return true;

}


bool ObjectStorage::print() {
    return true;
}
