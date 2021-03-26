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
    objects.push_back(std::move(obj));
    objectsMutex.unlock();
    return true;
}

bool ObjectStorage::removeFromTracking(Object *obj) {
    // identify in the vector where this object is stored
    // mark isValid = false


    // Caution: objects is mutating in code below
    /*for (vector<Object *>::iterator it = objects.begin();
         it!= objects.end(); it++) {
        Object *current = *it;
        if (obj->getName() == current->getName()) {
            objectsMutex.lock();
            current->setIsValid (false);
            objectsMutex.unlock();
        }
    }*/
    return true;

}


bool ObjectStorage::print() {
    cout << "--------------------------------------------------" << endl;
    cout << "Printing ObjectStorage " << endl;
    for (vector<unique_ptr<Object> >::iterator it = objects.begin();
         it!= objects.end(); it++) {
        Object *current = it->get();
        cout << "Name: " << current->getName() << ", Data: " << current->getData() << endl;
    }

    return true;
}


bool ObjectStorage::emptyObjectStorage() {
    cout << "--------------------------------------------------" << endl;
    cout << "Emptying ObjectStorage " << endl;
    for (vector<unique_ptr<Object> >::iterator it = objects.begin();
         it!= objects.end(); it++) {
        Object *current = it->get();
        //cout << "Deleting: " << current->getName() << ", Data: " << current->getData() << endl;
        Object *releasePtr = it->release();
        delete releasePtr;
    }
    return true;
}
