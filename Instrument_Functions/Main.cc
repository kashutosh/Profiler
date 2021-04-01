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
    void printC() {
        cout << "Printing C " << endl;
        vector<int> v;
        v.push_back(10); 
    }
};


int main() {
    // How would somebody detect that initialization happened here?
    initialization_complete = 1;
    printf("main is called \n");
    // There is practically no difference in calling 
    // callout (from external file) and foo (from same file)
    // here
    callout();
    foo();
    C * c = new C();
    c->printC();

    Aux a;
    a.init();
    delete c;
    return 0;
}


