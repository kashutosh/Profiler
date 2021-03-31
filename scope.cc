#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "scope.h"
#include "ObjectStorage.h"
#include "commons.h"
#include "MyObject.h"
using namespace std;

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

void f() {
     SCOPE_TIMER(1, "F_Scope");
     cout << "Inside function f\n";
}

int main() {
    {

        SCOPE_TIMER(1, "main");
        cout << "Some Random instructions\n";

        SCOPE_TIMER(2, "inner");


        for (int i=0;i<2;i++) {
            cout << "This is some random line\n";
        }
        SCOPE_TIMER(3, "outscope");
        f();
        ObjectStorage *os = ObjectStorage::getInstance();
        os->print();

    }
    ObjectStorage *os = ObjectStorage::getInstance();
    os->removeFromTracking(1);
    os->removeFromTracking(2);
    os->print();

    std::unique_ptr<Object> ptr1(createMyObject("object2", 99));
    os->registerForTracking(std::move(ptr1));
    std::unique_ptr<Object> ptr2(createMyObject("object2", 100));
    os->registerForTracking(std::move(ptr2));
    std::unique_ptr<Object> ptr3(createMyObject("object2", 101));
    os->registerForTracking(std::move(ptr3));


    os->emptyObjectStorage();
}
