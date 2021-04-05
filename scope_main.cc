#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "scope.h"
#include "ObjectStorage.h"
#include "commons.h"
#include "MyObject.h"
using namespace std;


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

