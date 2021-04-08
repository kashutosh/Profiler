#include "Trace.h"
#include "../Exception.h"

using namespace FlightRecorder;

hrtime gethrtime(void);

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
    fputs("node [ shape=record ];\n", fp);
    // Push one dummy frame for main

    FrameInformation f;
    f.address = 0;
    hrtime start_time = gethrtime();
    f.start_time = start_time;

    strcpy(f.function_name, "main");
    printf("Main Name Pushed is %s\n", f.function_name);
    s.push(f);
    initialization_complete = 1;
    return true;
}
