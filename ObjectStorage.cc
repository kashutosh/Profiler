#include "ObjectStorage.h"
#include <mutex>

using namespace std;

bool ObjectStorage::registerForTracking(Object *obj) {
    // Lock the objects vector
    objectsMutex.lock();
    objects.push_back(obj);
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
