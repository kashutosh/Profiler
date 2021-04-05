#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "scope.h"
#include "ObjectStorage.h"
#include "commons.h"
#include "MyObject.h"
using namespace std;

int Record::internal_level = 0;
Record::Record(string _name) : name(_name){
    start_timestamp = gethrtime();
    internal_level++;
    for (int i=0; i<internal_level; i++) {
        cout <<"--";
    }
    cout << "Begin scope "<< name << endl;
}
Record::~Record() {
    end_timestamp = gethrtime();
    for (int i=0; i<internal_level; i++) {
      cout <<"--";
    }
    cout << "The time taken in scope " << name << " is " << end_timestamp - start_timestamp << endl;

    std::unique_ptr<Object> ptr(createMyObject("object1", end_timestamp - start_timestamp));
    ObjectStorage *os = ObjectStorage::getInstance();

    // handover the ownership of this pointer to ObjectStorage
    // std::move invokes a destructor on created object
    os->registerForTracking(std::move(ptr));
    internal_level--;
}

