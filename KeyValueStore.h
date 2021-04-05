#ifndef KEYVALUESTORE_H
#define KEYVALUESTORE_H

#include <iostream>
#include <map>
#include <string>

using namespace std;

namespace FlightRecorder {
class KeyValueStore {

private:
    map<string, string> keyValuePairs;
    KeyValueStore();
    static KeyValueStore *keyvalue_store;
public:
    bool print();

    static KeyValueStore *getInstance() {
        if (keyvalue_store == nullptr) {
            keyvalue_store = new KeyValueStore();
        }
        return keyvalue_store;
    } 

    int getObjectsCount() const;

    bool emptyKeyValueStore();

    bool checkIfThisKeyExists(const string key);

    string getValue(const string key) const;


    // Utility functions to convert common types to string
    
    string to_string (int val) const { return std::to_string(val); }
    string to_string (long val) const { return std::to_string(val); }
    string to_string (long long val) const { return std::to_string(val); }
    string to_string (unsigned val) const { return std::to_string(val); }
    string to_string (unsigned long val) const { return std::to_string(val); }
    string to_string (unsigned long long val) const { return std::to_string(val); }
    string to_string (float val) const { return std::to_string(val); }
    string to_string (double val) const { return std::to_string(val); }
    string to_string (long double val) const { return std::to_string(val); }


    string getUniqueName() ;

};
}
#endif
