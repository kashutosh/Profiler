#ifndef MYOBJECT_H
#define MYOBJECT_H

#include <iostream>
#include <vector>
#include <mutex>
#include <memory>
#include "Object.h"

using namespace std;

class MyObject : public Object{
    int i;
public:
    MyObject(string name, int i) 
            : Object(name), i(i)
    {
    }

    ~MyObject() {
        cout << "MyObject destructor is called " << endl;
    }

public:
    friend std::unique_ptr<Object> createMyObject(const string name, const int auxdata);

};

std::unique_ptr<Object> createMyObject(const string name, const int auxdata);



#endif
