#include "Trace.h"
#define MAX_STACK_DEPTH 200


Stack::Stack() {
    printf ("Creating stack \n");
    index = -1;
}

void Stack::push(Dummy frame) {
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
    return index;
}
