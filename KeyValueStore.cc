#include "KeyValueStore.h"

using namespace std;

namespace FlightRecorder{
KeyValueStore *KeyValueStore ::keyvalue_store = nullptr;


bool KeyValueStore::print() {
    return true;
}

int KeyValueStore::getObjectsCount() const{
    return this->keyValuePairs.size();
}

bool KeyValueStore::emptyKeyValueStore() {
    return true;
}

bool KeyValueStore::checkIfThisKeyExists(const string key) {
    if (keyValuePairs.find(key) == keyValuePairs.end())
        return false;
    else
        return true;
}

string KeyValueStore::getValue(const string key) const {
    std::map<string, string>::const_iterator it = this->keyValuePairs.find(key);
    if (it == keyValuePairs.end())
        return "";
    else
        return it->second;
}

string KeyValueStore::getUniqueName() {
    // These two are static within the function
    static string prefix = "unique";
    static unsigned int counter = 0;
    counter++;
    string nextname = prefix;
    while (true) {
        nextname = prefix + to_string(counter);
        if (KeyValueStore::checkIfThisKeyExists(nextname) == false) {
            break;
        }
    }
    return nextname;
}

}
