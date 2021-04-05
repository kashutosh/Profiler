#include "Trace.h"
#include "../Exception.h"

using namespace FlightRecorder;




void FunctionTracer::initializeTracer() {
    extern Stack s;
    extern int initialization_complete;
    initialization_complete = 1;
    s.push(FrameInformation());
}
