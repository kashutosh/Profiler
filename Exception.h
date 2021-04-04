#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <iostream>
#include <exception>
#include <string>
using namespace std;


class Exception : public exception{
private:
    string msg_;
public:
    Exception (Exception &e) {
        cout << "Copy constructor of exception is called " << endl;
        this->msg_ = e.msg_;
    }
    Exception(const char *message) : msg_(message){
        cout << "Created exception with message " << msg_ << this<< endl;
    }

    virtual const char* what() const throw() {
        cout << "Returning " << msg_.c_str() << this << endl;
        return msg_.c_str();
    }
};

#endif
