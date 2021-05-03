#include <stdio.h>
#include <dlfcn.h>
#include <iostream>
#include <stdlib.h>
#include <pthread.h>

#include "Trace.h"
#include "FunctionTracer.h"
#include <cxxabi.h>

#include "hashtable.h"
#include "LinkedListOfFrames.h"
using namespace FlightRecorder;
#define MAX_THREADS_TO_TRACE 71

#ifdef __cplusplus
using namespace std;

hrtime gethrtime (void) __attribute__((no_instrument_function));
__inline__ hrtime gethrtime (void) 
{
  unsigned hi, lo;
  __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
  return ( (unsigned long long)lo)|( ((unsigned long long)hi)<<32 );
}


extern "C"
{
    void __cyg_profile_func_enter(void *this_fn, void *call_site)
        __attribute__((no_instrument_function));
    void __cyg_profile_func_exit(void *this_fn, void *call_site)
        __attribute__((no_instrument_function));
}
#endif



Stack stacks[MAX_THREADS_TO_TRACE];
// When we enter the function, this block of code executes
void __cyg_profile_func_enter(void* this_fn, void* call_site)
{
    if (!initialization_complete) return;

    int threadid = pthread_self();
    // Find an identifier of Stack on which this frame should be pushed
    int idx = FlightRecorder::find(threadid);
    if (idx == -1 ) {
        //printf("Found that threadid %d does not exist in hashtable when pushing a frame\n", threadid);
        idx = FlightRecorder::insert(threadid);
        //printf("Result of insert operation is: Threadid:%d, Index:%d\n", threadid, idx);
    }

    FunctionTracer::id[idx]++;
    // Do not do address translations right here?

    void *address = this_fn;
    void *call_site_addr = call_site;
    hrtime start_time = gethrtime();
    hrtime end_time = 0;


    FrameInformation * d = (FrameInformation*) malloc(sizeof (FrameInformation));
    d->threadid = threadid;
    d->address = address;
    d->call_site = call_site_addr;
    d->start_time = start_time;
    d->end_time = end_time;
    d->id = FunctionTracer::id[idx];

    d->operation = PUSH;
    FlightRecorder::appendNodeToTailOfAList(d, idx);
}

void __cyg_profile_func_exit(void* this_fn, void* call_site)
{
    if (!initialization_complete) return;
    Dl_info info_current;
    hrtime end_time = gethrtime();
    
    int threadid = pthread_self();
    int idx = FlightRecorder::find(threadid);
    //printf("TRACE: Popping with threadid %d on index %d\n", threadid, idx);
   
    FrameInformation *fpop = (FrameInformation*) malloc(sizeof(FrameInformation));
    fpop->threadid = threadid;
    fpop->address = this_fn;
    fpop->call_site = call_site;
    fpop->end_time = end_time;
    fpop->operation = POP;
    FlightRecorder::appendNodeToTailOfAList(fpop, idx);


}


/*
digraph { 
node [ shape=record ];
 p3 -> p4 [label="4"] 
 p4 [label= "{callout4() | Threadid: 3048204096 | Time: 0.056 ms| Lib: ./FunctionTracer }" ];
 p2 -> p3 [label="3"] 
 p3 [label= "{callout3() | Threadid: 3048204096 | Time: 0.232 ms| Lib: ./FunctionTracer }" ];
 p1 -> p2 [label="2"] 
 p2 [label= "{callout2() | Threadid: 3048204096 | Time: 0.329 ms| Lib: ./FunctionTracer }" ];
 p6 -> p7 [label="7"] 
 p7 [label= "{callout4() | Threadid: 3048204096 | Time: 0.055 ms| Lib: ./FunctionTracer }" ];
 p5 -> p6 [label="6"] 
 p6 [label= "{callout3() | Threadid: 3048204096 | Time: 0.139 ms| Lib: ./FunctionTracer }" ];
 p1 -> p5 [label="5"] 
 p5 [label= "{callout2() | Threadid: 3048204096 | Time: 0.221 ms| Lib: ./FunctionTracer }" ];
 p0 -> p1 [label="1"] 
 p1 [label= "{callout() | Threadid: 3048204096 | Time: 0.709 ms| Lib: ./FunctionTracer }" ];
 p0 -> p8 [label="8"] 
 p8 [label= "{foo() | Threadid: 3048204096 | Time: 0.040 ms| Lib: ./FunctionTracer }" ];
 p0 -> p9 [label="9"] 
 p9 [label= "{C::C() | Threadid: 3048204096 | Time: 0.021 ms| Lib: ./FunctionTracer }" ];
 p10 -> p11 [label="11"] 
 p11 [label= "{C::internal() | Threadid: 3048204096 | Time: 0.047 ms| Lib: ./FunctionTracer }" ];
 p0 -> p10 [label="10"] 
 p10 [label= "{C::printC() | Threadid: 3048204096 | Time: 0.138 ms| Lib: ./FunctionTracer }" ];
 p0 [label= "{main |Time: 9223332167680.000 ms}" ];
}
*/
