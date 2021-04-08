#include <stdio.h>
#include <dlfcn.h>
#include <iostream>
#include <stdlib.h>
#include <pthread.h>

#include "Trace.h"
#include "Aux.h"

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

    // Do not do address translations right here?
    Dl_info info;
    printf("entering %p @@", (void*)(int*)this_fn);
    printf(";call_site %p @@", (void*)(int*)call_site);

    uint threadid = pthread_self();
    ulint address = (ulint)((void*)(ulint*) this_fn);
    ulint call_site_addr = (ulint)((void *) (ulint*) call_site);
    hrtime start_time = gethrtime();
    hrtime end_time = start_time;

    printf ("start time %llu\n", start_time);

    //int translation_result = dladdr(this_fn, &info);
    if (dladdr(this_fn, &info)) {
        printf("[%s] ",info.dli_sname ? info.dli_sname : "unknown");
        printf("[%s]\n",info.dli_fname ? info.dli_fname : "unknown");
    }
    FrameInformation d (threadid, address, call_site_addr, start_time, end_time);
    
    s.push(d);
}

void __cyg_profile_func_exit(void* this_fn, void* call_site)
{
    if (!initialization_complete) return;
    Dl_info info;
    printf("exiting %p @@", (void *)(int*)this_fn);
    printf(";call_site %p @@", (void*)(int*)call_site);
    hrtime end_time = gethrtime();
    if (dladdr(this_fn, &info)) {
        printf("[%s] ",info.dli_sname ? info.dli_sname : "unknown");
        printf("[%s]\n",info.dli_fname ? info.dli_fname : "unknown");
    }
    s.pop();

}

