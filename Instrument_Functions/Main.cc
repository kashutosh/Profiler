//#include <iostream>
#include "Trace.h"
using namespace std;
extern int global;
int initialization_complete = 0;
void callout();

void foo() {
//    cout << "foo " << endl;
}

class C {
public:
    C() {
    }
    ~C() {

    }
    void printC() {
//        cout << "Printing C " << endl;
    }
};


int main() {
    // How would somebody detect that initialization happened here?
    initialization_complete = 1;
    callout();
    foo();
    C * c = new C();
    c->printC();
    delete c;
    return 0;
}


