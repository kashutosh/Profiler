#include "Trace.h"
#include "FunctionTracer.h"
#include "../Exception.h"
#include "hashtable.h"
#include <cxxabi.h>
#include "LinkedListOfFrames.h"

using namespace FlightRecorder;

hrtime gethrtime(void);

FILE * FunctionTracer::fp;
int FunctionTracer::id = 0;
float FunctionTracer::clock_speed = 2.0;
extern Stack stacks[NUM_THREADS_PRIME];
int initialization_complete = 0;

bool FunctionTracer::initializeTracer(float clock_speed_) {
    extern Stack s;
    extern int initialization_complete;

    FlightRecorder::initializeBuckets();
    FlightRecorder::initializeLinkedLists();

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

    FrameInformation *f = (FrameInformation*) malloc(sizeof(FrameInformation));
    int threadid = pthread_self();
    f->threadid = threadid;

    // NOTICE THIS LINE CAREFULLY
    f->address = (void*)&FunctionTracer::initializeTracer;
    f->call_site = (void*)FunctionTracer::initializeTracer;
    hrtime start_time = gethrtime();
    f->start_time = start_time;
    f->end_time = start_time;
    f->id = 0;
    f->operation = PUSH;


    int idx = FlightRecorder::find(threadid);
    if (idx == -1 ) {
        printf("Found that threadid %d does not exist in hashtable when pushing a frame\n", threadid);
        idx = FlightRecorder::insert(threadid);
        printf("Result of insert operation is: Threadid:%d, Index:%d\n", threadid, idx);
    }

    printf("FNTR: Pushing with threadid %d on index %d\n", threadid, idx);
    FlightRecorder::appendNodeToTailOfAList(f, idx);

    //strcpy(f.function_name, "main");
    //printf("Main Name Pushed is %s\n", f.function_name);
    //s.push(f);

    /*for (int i=0; i<71; i++) {
        stacks[i].push(f);
    }*/
    initialization_complete = 1;
    return true;
}




bool FunctionTracer::stopTracer() {
    if (fp == NULL) {
        return false;
    }



/*
    char buffer[2000];
    extern Stack s;
    int threadid = pthread_self();
    hrtime end_time = gethrtime();
    int idx = FlightRecorder::find(threadid);
    FrameInformation &top_frame = stacks[idx].getFrame(stacks[idx].top());
    top_frame.end_time = end_time;
    top_frame.threadid = threadid;

    void *top_frame_addr = top_frame.address;
    Dl_info info_top;
    char top_function_name[400];
    char top_library_name[400];
    // Decode this address
    if (dladdr(top_frame_addr, &info_top)) {
        //printf(" [%s] ",info_top.dli_sname ? info_top.dli_sname : "unknown");
        //printf(" [%s]\n",info_top.dli_fname ? info_top.dli_fname : "unknown");
        if (info_top.dli_sname) {
            strcpy(top_function_name, info_top.dli_sname);
        }
        else {
            strcpy(top_function_name, "unknown name");
        }
        if (info_top.dli_fname) {
            strcpy(top_library_name, info_top.dli_fname);
        }
        else {
            strcpy(top_library_name, "unknown library");
        }

    }

    //sprintf(buffer, " p%d [label= \"{%s |Time: %.3f ms}\" ];\n", top_frame.id, top_frame.function_name, (top_frame.end_time-top_frame.start_time)/(FunctionTracer::clock_speed*1000*1000));
    int status;
    sprintf(buffer, " p%d [label= \"{%s | Threadid: %u | Time: %.3f ms| Lib: %s }\" ];\n", top_frame.id, abi::__cxa_demangle(top_function_name, 0, 0, &status), top_frame.threadid, (top_frame.end_time-top_frame.start_time)/(FunctionTracer::clock_speed*1000*1000), top_library_name);
    fputs(buffer, FunctionTracer::fp);

*/


    FrameInformation *fpop = (FrameInformation*) malloc(sizeof(FrameInformation));
    int threadid = pthread_self();
    fpop->threadid = threadid;
    fpop->address = (void*)&FunctionTracer::stopTracer;
    fpop->call_site = (void*)FunctionTracer::stopTracer;
    fpop->start_time = 0;
    hrtime end_time = gethrtime();
    fpop->end_time = end_time;
    fpop->operation = POP;
    FlightRecorder::appendNodeToTailOfAList(fpop, idx);




    FlightRecorder::printTheListsOutToAFile();


    fputs("}\n", fp);
    fclose(fp);
    FunctionTracer::id=0;

    printf("Number of stacks created were %d\n", FlightRecorder::getNumKeysStored());
    return true;
}
 

