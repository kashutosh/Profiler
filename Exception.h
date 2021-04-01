#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>
#include <string>
using namespace std;


class Exception : public exception{
private:
    string msg_;
public:
    Exception (Exception &e) {
    }
    Exception(const char *message) : msg_(message){
    }

    /*virtual void setMessage(string message) {
    }*/
    virtual const char* what() const throw() {
        return msg_.c_str();
    }
};

#endif
