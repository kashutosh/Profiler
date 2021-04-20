#ifndef AUX_H
#define AUX_H

#include <iostream>
#include <vector>
#include <map>
using namespace std;

class Aux {

public:
    Aux() __attribute__((no_instrument_function)) {}

    vector<int> v;
    map<int, int> m;

    void init() __attribute__((no_instrument_function)) {
        v.push_back(1);
        v.push_back(1);
        v.push_back(1);
        v.push_back(1);
        v.push_back(1);
        v.push_back(1);
        //m.insert(make_pair<int,int>(10,10));
    }

};

void callout4();
void benchmark_sleep();
#endif

