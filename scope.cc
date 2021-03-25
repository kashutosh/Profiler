#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "scope.h"
using namespace std;


void f() {
     PROF_SCOPE(1, "F_Scope");
     cout << "Inside function f\n";
}

int main() {
    {
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
