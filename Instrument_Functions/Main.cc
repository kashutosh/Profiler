#include <iostream>
using namespace std;


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
    foo();
    C * c = new C();
    c->printC();
    delete c;
    return 0;
}


