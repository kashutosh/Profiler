#include "Trace.h"
#include "FunctionTracer.h"
#include "../Exception.h"
#include "hashtable.h"
#include <cxxabi.h>
#include "LinkedListOfFrames.h"
#include "Aggregate_Stacks.h"

using namespace FlightRecorder;

hrtime gethrtime(void);

FILE * FunctionTracer::fp;
FILE * FunctionTracer::fptext;
int FunctionTracer::id [NUM_BUCKETS_PRIME] = {0};
float FunctionTracer::clock_speed = 2.0;
extern Stack stacks[NUM_BUCKETS_PRIME];
int initialization_complete = 0;
hrtime FunctionTracer::execution_start_time = 0;

bool FunctionTracer::initializeTracer(float clock_speed_, void *caller_ptr) {
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

    fptext = fopen ("/tmp/callstack.txt", "w");

    if (fptext == NULL) {
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
    //f->address = (void*)&FunctionTracer::initializeTracer;
    //f->call_site = (void*)FunctionTracer::initializeTracer;

    f->address = caller_ptr;
    f->call_site = caller_ptr;

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

    execution_start_time = start_time;

    initialization_complete = 1;
    return true;
}




bool FunctionTracer::stopTracer(void *caller_ptr) {
    if (fp == NULL) {
        return false;
    }


    FrameInformation *fpop = (FrameInformation*) malloc(sizeof(FrameInformation));
    int threadid = pthread_self();
    fpop->threadid = threadid;
    //fpop->address = (void*)&FunctionTracer::initializeTracer;
    //fpop->call_site = (void*)FunctionTracer::initializeTracer;

    fpop->address = caller_ptr;
    fpop->call_site = caller_ptr;
    fpop->start_time = 0;
    hrtime end_time = gethrtime();
    fpop->end_time = end_time;
    fpop->operation = POP;

    int idx = FlightRecorder::find(threadid);
    FlightRecorder::appendNodeToTailOfAList(fpop, idx);




    FlightRecorder::printTheListsOutToAFile();


    fputs("}\n", fp);
    fclose(fp);
    fclose(fptext);
    for (int i=0; i<NUM_BUCKETS_PRIME; i++) {
        FunctionTracer::id[i]=0;
    }

    FlightRecorder::aggregateStacks();

    printf("Number of stacks created were %d\n", FlightRecorder::getNumKeysStored());
    return true;
}
 

