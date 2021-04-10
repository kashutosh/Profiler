#include <stdio.h>
#include <dlfcn.h>
#include <iostream>
#include <stdlib.h>
#include <pthread.h>

#include "Trace.h"
#include "FunctionTracer.h"

//typedef unsigned long long hrtime;
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


Stack s;
// When we enter the function, this block of code executes
void __cyg_profile_func_enter(void* this_fn, void* call_site)
{
    if (!initialization_complete) return;

    FunctionTracer::id++;
    // Do not do address translations right here?
    Dl_info info;
    printf("entering %p @@", (void*)(int*)this_fn);
    printf(";call_site %p @@", (void*)(int*)call_site);

    uint threadid = pthread_self();
    void *address = this_fn;
    void *call_site_addr = call_site;
    hrtime start_time = gethrtime();
    hrtime end_time = start_time;

    printf ("start time %llu\n", start_time);

    //int translation_result = dladdr(this_fn, &info);
    if (dladdr(this_fn, &info)) {
        printf("[%s] ",info.dli_sname ? info.dli_sname : "unknown");
        printf("[%s]\n",info.dli_fname ? info.dli_fname : "unknown");
    }
    FrameInformation d (threadid, address, call_site_addr, start_time, end_time);
    strcpy(d.function_name, info.dli_sname);
    strcpy(d.library_name, info.dli_fname);
    d.id = FunctionTracer::id;
    //d.print();
    s.push(d);
}

void __cyg_profile_func_exit(void* this_fn, void* call_site)
{
    if (!initialization_complete) return;
    Dl_info info_current;
    printf("exiting %p @@", (void *)(int*)this_fn);
    printf(";call_site %p @@", (void*)(int*)call_site);
    hrtime end_time = gethrtime();
    // Translate addresses of current function

    if (dladdr(this_fn, &info_current)) {
        printf("[%s] ",info_current.dli_sname ? info_current.dli_sname : "unknown");
        printf("[%s]\n",info_current.dli_fname ? info_current.dli_fname : "unknown");
    }
    FrameInformation &d = s.getFrame(s.top()-1);
    FrameInformation &top_frame = s.getFrame(s.top());
    top_frame.end_time = end_time;
    printf("Time taken by function is %llu\n", top_frame.end_time - top_frame.start_time);


    // Translate addresses of calling function
//    Dl_info info_parent;
//    printf("parent info \n");
    char buffer[2000];
/**
*
    sprintf(buffer, " %s -> %s [label=\"Time: %llu\"]\n", d.function_name, info_current.dli_sname, d.end_time - d.start_time);
    fputs(buffer, FunctionTracer::fp);

    Perhaps print another node for metadata. We are interested only in edges?

    sprintf(buffer, " p%p [label=\"%s\" ]; \n",  this_fn, info_current.dli_sname);
    fputs(buffer, FunctionTracer::fp);
**/

     // Consider Enabling these lines.
//    sprintf(buffer, " p%d [label= \"{-1 %s | %llu}\" ];\n", d.id, d.function_name, top_frame.end_time-top_frame.start_time);
//    fputs(buffer, FunctionTracer::fp);

    sprintf(buffer, " p%d -> p%d [label=\"%d\"] \n", d.id, top_frame.id, top_frame.id);
    fputs(buffer, FunctionTracer::fp);


    sprintf(buffer, " p%d [label= \"{%s | Threadid: %u | Time: %.3f ms| Lib: %s}\" ];\n", top_frame.id, top_frame.function_name, top_frame.threadid, (top_frame.end_time-top_frame.start_time)/(FunctionTracer::clock_speed*1000*1000), top_frame.library_name);
    fputs(buffer, FunctionTracer::fp);

    s.pop();

}

/*
digraph { 
 node [ shape=record ];
 A [label="{main | time=100000 | field3}"];
 B [label="_ZN1C6printCEv" ];
 A -> B
 C [label="_ZN1C8internalEv" ];
 B -> C

}
*/
