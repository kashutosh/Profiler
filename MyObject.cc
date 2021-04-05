#include "MyObject.h"
#include <memory>
using namespace std;

namespace FlightRecorder {
std::unique_ptr<Object> createMyObject(const string name, const int auxdata) {
    MyObject * o = new MyObject(name, auxdata);
    std::unique_ptr<Object> uptr(o);
    return uptr;
}

}
