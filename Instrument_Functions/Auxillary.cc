#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
#include "Auxillary.h"
#include "Trace.h"


vector<string> v;


void callout4() {
    //sleep(1);
}
void callout3() {
    std::cout << "Cout called from callout " << std::endl;
    for (int i=0; i<4; i++) {
        v.push_back("foobar");
    }
    callout4();
}
void callout2() {
    callout3();
    std::cout << "Cout called from callout " << std::endl;
}
void callout() {
    callout2();
    std::cout << "Cout called from callout " << std::endl;
    for (int i=0;i<3;i++) {
        callout2();
    }
}
