#include "ObjectStorage.h"
#include <memory>

using namespace std;

namespace FlightRecorder {
// These functions are friends to Object class
std::unique_ptr<Object> createObject(string name);
std::unique_ptr<Object> createObject();

}
