#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "scope.h"
#include "ObjectStorage.h"
#include "commons.h"
using namespace std;

Record::Record(string _name) {
    name = _name;
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

    std::unique_ptr<Object> ptr(createObject("object1", 1));
    ObjectStorage *os = ObjectStorage::getInstance();

    // handover the ownership of this pointer to ObjectStorage
    os->registerForTracking(std::move(ptr));
    internal_level--;
}

void f() {
     PROF_SCOPE(1, "F_Scope");
     cout << "Inside function f\n";
}

int main() {
    {

        ObjectStorage profile_objects;
        PROF_SCOPE(1, "main");
        cout << "Some Random instructions\n";
        PROF_SCOPE(2, "inner");
        for (int i=0;i<2;i++) {
            cout << "This is some random line\n";
        }
        PROF_SCOPE(3, "outscope");
        f();
    }
}
