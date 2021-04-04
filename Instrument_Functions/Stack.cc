#include "Trace.h"
#include "../Exception.h"
#define MAX_STACK_DEPTH 200


Stack::Stack() {
    printf ("Creating stack \n");
    index = -1;
}

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
    Dummy d;
    // When main is exited, event then pop is called
    // So is case when main entered
    // if (index <= 0) return d;
    d = frames[index];
    index--;
    return d;
}

int Stack::numFrames() {
    return index+1;
}
