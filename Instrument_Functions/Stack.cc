#include "Trace.h"
#include "../Exception.h"
#define MAX_STACK_DEPTH 200

using namespace FlightRecorder;

Stack::Stack() {
    printf ("Creating stack \n");
    index = -1;
}


// Why should this be copy by value?
void Stack::push(Dummy frame) {
    if (index == (MAX_STACK_DEPTH-1) ) {
        cout << "Throwing an exception \n";
        Exception e("Stack Overflowed beyond capacity");
        throw e;
    }
    index++;
    frames[index] = frame;
}

Dummy Stack::pop() {
    // When main is exited, event then pop is called
    // So is case when main entered
    if (index < 0) {
        Exception e("Stack underflow");
        throw e;
    }
    index--;
    return frames[index];
}

int Stack::numFrames() {
    return index+1;
}


