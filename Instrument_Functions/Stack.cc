#include "Trace.h"
#include "../Exception.h"
#include <fstream>
#define MAX_STACK_DEPTH 200

using namespace FlightRecorder;


Stack::Stack() {
    //printf ("Creating stack \n");
    index = -1;
}


// Why should this be copy by value?
void Stack::push(FrameInformation frame) {
    if (index == (MAX_STACK_DEPTH-1) ) {
        cout << "Throwing an exception \n";
        Exception e("Stack Overflowed beyond capacity");
        throw e;
    }
    index++;
    frames[index] = frame;
}

FrameInformation Stack::pop() {
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

int Stack::top() {
    return index;
}



bool Stack::printStackFrames(const char *filename) {
    // Open the file with given file name

    // Should not use c++ primitives as long as possible, isn't it?
    ofstream outfile;
    outfile.open(filename, ios::out);

    if (!outfile.is_open()) {
        Exception e("Unable to open file " );
        throw e;
    }


    outfile.close();
    return true;
}

FrameInformation &Stack::getFrame(int index) {
     if (index <=0 || index > MAX_STACK_DEPTH) {
         return frames[0];
     }
     return frames[index];
}
