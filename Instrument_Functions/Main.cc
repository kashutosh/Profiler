#include <iostream>
#include "Trace.h"
using namespace std;
int initialization_complete = 0;

void foo() {
    cout << "foo " << endl;
}

class C {
public:
    C() {
    }
    ~C() {

    }
    void printC() {
        cout << "Printing C " << endl;
    }
};


int main() {
    initialization_complete = 1;
    foo();
    C * c = new C();
    c->printC();
    delete c;
    return 0;
}


