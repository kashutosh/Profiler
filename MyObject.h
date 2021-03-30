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
    MyObject(string name, double data, int i) 
            : Object(name, data) 
    {
        this->i = i;
    }

    ~MyObject() {
        cout << "MyObject destructor is called " << endl;
    }

public:
    friend std::unique_ptr<Object> createMyObject(string name, double data, int auxdata);

};

std::unique_ptr<Object> createMyObject(string name, double data, int auxdata);



#endif
