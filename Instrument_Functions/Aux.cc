#include <iostream>
#include "Aux.h"

using namespace std;

void callout() {
    Aux a;
    a.init();

    cout << "Cout called from callout " << endl;
}
