#include <pthread.h>
#include "Trace.h"
#include "FunctionTracer.h"
#include <cxxabi.h>

#include "hashtable.h"
#include "LinkedListOfFrames.h"
#include "Auxillary.h"

using namespace FlightRecorder;
#define ITERATIONS 100000

// Mimic Overhead Of Operations
// 1 function call for __enter
// 1 function call for __exit
// 1 pthread_self
// 2 hrtime_t gethrtime()
// 2 Stack.push operations
// Do these operations 10000 times and find the overhead

hrtime gethrtime(void);

void dummy_function(void * a1, void *a2)  {

}
// Type 1 benchmarker. Mimic Operations. Mimic overhead by a function call
// that looks similar

void benchmark() {

    FlightRecorder::initializeBuckets();
    FlightRecorder::initializeLinkedLists();
    hrtime bm_start_time = gethrtime();
    for (int i=0;i<ITERATIONS;i++) {
        int threadid = pthread_self();
        dummy_function((void*)0, (void*)1); // mimic __enter
        void *address = 0;
        void *call_site_addr = 0;
        hrtime start_time = gethrtime();
        hrtime end_time = 0;


        FrameInformation * d = (FrameInformation*) malloc(sizeof (FrameInformation));
        d->threadid = threadid;
        d->address = address;
        d->call_site = call_site_addr;
        d->start_time = start_time;
        d->end_time = end_time;

        // Find an identifier of Stack on which this frame should be pushed
        int idx = FlightRecorder::find(threadid);
        if (idx == -1 ) {
            idx = FlightRecorder::insert(threadid);
        }
        d->id = FunctionTracer::id[idx]++;
        d->operation = PUSH;
        FlightRecorder::appendNodeToTailOfAList(d, idx);

    }
    hrtime bm_end_time = gethrtime();
    printf("Average CPU cycles per function call = %.1f\n", (float)(2.0*(bm_end_time - bm_start_time)/ITERATIONS));

}


// type 2 benchmarker. add some functions and in reality, link them with 
// our Trace.cc.
// e.g. one can modify main.cc to achieve the same thing




