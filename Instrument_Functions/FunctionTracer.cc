#include "Trace.h"
#include "../Exception.h"

using namespace FlightRecorder;


FILE * FunctionTracer::fp;
bool FunctionTracer::stopTracer() {
    if (fp == NULL) {
        return false;
    }
    fputs("}\n", fp);
    fclose(fp);
    return true;
}
 

bool FunctionTracer::initializeTracer() {
    extern Stack s;
    extern int initialization_complete;

    // Open the file handle and start writing a graph into it

    fp = fopen ("/tmp/callstack.dot", "w");

    if (fp == NULL) {
        printf("Unable to open the file to be written \n");
        return false;    
    }

    fputs("digraph { \n", fp);
    // Push one dummy frame for main
    s.push(FrameInformation());
    initialization_complete = 1;
    return true;
}
