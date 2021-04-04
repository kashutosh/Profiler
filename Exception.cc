#include "Exception.h"
#include <iostream>
#include <typeinfo>
using namespace std;

class Polymorphic {virtual void member(){}};
void foo() {

  try
  {
    Polymorphic * pb = 0;
    typeid(*pb);  // throws a bad_typeid exception
  }
  catch (std::exception& e)
  {
    std::cerr << "exception caught: " << e.what() << '\n';
    //throw;
  }

    string s("Hit an exception in foo function and I am throwing it");
    Exception e(s.c_str());
    throw e;
}

int main() {
    string s("Hit an exception");
    Exception e(s.c_str());
    cout << e.what() << endl;

    try {
        foo();
    }
    catch (Exception &e) {
        cout << e.what() << endl;
    }
    catch (exception &e) {

        cout << "Exception caught in main " << e.what() << endl;
    }
    return 0;
}
