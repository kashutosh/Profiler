#include <iostream>
#include "Aux.h"

using namespace std;

void callout3() {
    cout << "Cout called from callout " << endl;
}
void callout2() {
    callout3();
    cout << "Cout called from callout " << endl;
}
void callout() {
    callout2();
    cout << "Cout called from callout " << endl;
    for (int i=0;i<1000000;i++) {
        i=i*2;
        i = i<<2;
    }
}
