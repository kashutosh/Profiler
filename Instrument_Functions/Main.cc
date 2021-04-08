#include <iostream>
#include "Trace.h"
#include <vector>
#include "Aux.h"
using namespace std;
extern int global;
int initialization_complete = 0;
void callout();

void foo() {
    cout << "foo " << endl;
}

class C {
public:
    C() {
    }
    ~C() {

    }
    void internal() { cout << "This is an internal function " << endl; }
    void printC() {

        internal();
        cout << "Printing C " << endl;
        vector<int> v;
        v.push_back(10); 
    }
};


int main() {
    // How would somebody detect that initialization happened here?
    FunctionTracer::initializeTracer();
    printf("main is called \n");
    // There is practically no difference in calling 
    // callout (from external file) and foo (from same file)
    // here
    callout();
    foo();
    C * c = new C();
    c->printC();

    //Aux a;
    //a.init();
    FunctionTracer::stopTracer();
    delete c;
//    extern Stack s;
//    s.printStackFrames("/tmp/foo.out");
    return 0;
}


