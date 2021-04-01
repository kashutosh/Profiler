#include <stdio.h>
#include <dlfcn.h>
#include <iostream>
#include <stdlib.h>
#include <pthread.h>

#include "Trace.h"
#include "Aux.h"

#ifdef __cplusplus
using namespace std;
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
    Dl_info info;
    printf("entering %p @@", (void*)(int*)this_fn);
    if (dladdr(this_fn, &info)) {
        printf("[%s] ",info.dli_sname ? info.dli_sname : "unknown");
        printf("[%s]\n",info.dli_fname ? info.dli_fname : "unknown");
    }
    Dummy d;
    s.push(d);
}

void __cyg_profile_func_exit(void* this_fn, void* call_site)
{
    if (!initialization_complete) return;
    Dl_info info;
    printf("exiting %p @@", (void *)(int*)this_fn);
    if (dladdr(this_fn, &info)) {
        printf("[%s] ",info.dli_sname ? info.dli_sname : "unknown");
        printf("[%s]\n",info.dli_fname ? info.dli_fname : "unknown");
    }
    s.pop();

}

