#include "Trace.h"
#include "FunctionTracer.h"
#include "../Exception.h"
#include "hashtable.h"
#include <cxxabi.h>

using namespace FlightRecorder;

hrtime gethrtime(void);

FILE * FunctionTracer::fp;
int FunctionTracer::id = 0;
float FunctionTracer::clock_speed = 2.0;
extern Stack stacks[71];
int initialization_complete = 0;
bool FunctionTracer::stopTracer() {
    if (fp == NULL) {
        return false;
    }
    char buffer[300];
    extern Stack s;
    int threadid = pthread_self();
    hrtime end_time = gethrtime();
    FrameInformation &top_frame = s.getFrame(s.top());
    top_frame.end_time = end_time;
    top_frame.threadid = threadid;
    //sprintf(buffer, " p%d [label= \"{%s |Time: %.3f ms}\" ];\n", top_frame.id, top_frame.function_name, (top_frame.end_time-top_frame.start_time)/(FunctionTracer::clock_speed*1000*1000));
    int status;
    sprintf(buffer, " p%d [label= \"{%s | Threadid: %u | Time: %.3f ms| Lib: %s }\" ];\n", top_frame.id, abi::__cxa_demangle(top_frame.function_name, 0, 0, &status), top_frame.threadid, (top_frame.end_time-top_frame.start_time)/(FunctionTracer::clock_speed*1000*1000), top_frame.library_name);
    fputs(buffer, FunctionTracer::fp);
    fputs("}\n", fp);
    fclose(fp);

    printf("Number of stacks created were %d\n", FlightRecorder::getNumKeysStored());
    return true;
}
 

bool FunctionTracer::initializeTracer(float clock_speed_) {
    extern Stack s;
    extern int initialization_complete;

    FlightRecorder::initializeBuckets();

    // Open the file handle and start writing a graph into it
 
    clock_speed = clock_speed_;

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

    for (int i=0; i<11; i++) {
        stacks[i].push(f);
    }
    initialization_complete = 1;
    return true;
}
