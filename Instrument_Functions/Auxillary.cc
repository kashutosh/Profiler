#include <iostream>
#include <vector>
#include <string>
#include "Auxillary.h"

using namespace std;

vector<string> v;

void callout4() {
    cout << "Cout called from callout 4" << endl;
    cout << v.size () << endl;
}
void callout3() {
    cout << "Cout called from callout " << endl;
    for (int i=0; i<4; i++) {
        v.push_back("foobar");
    }
    callout4();
}
void callout2() {
    callout3();
    cout << "Cout called from callout " << endl;
}
void callout() {
    callout2();
    cout << "Cout called from callout " << endl;
    for (int i=0;i<3;i++) {
        callout2();
    }
}
