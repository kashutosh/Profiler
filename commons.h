#include "ObjectStorage.h"
#include <memory>

using namespace std;

// These functions are friends to Object class
std::unique_ptr<Object> createObject(string name, double data);
std::unique_ptr<Object> createObject();


