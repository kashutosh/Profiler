#include <iostream>
#include "Aux.h"

using namespace std;

void callout() {
    cout << "Cout called from callout " << endl;
    for (int i=0;i<1000000;i++) {
        i=i*2;
        i = i<<2;
    }
}
