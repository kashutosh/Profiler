#ifndef TRACE_H
#define TRACE_H

#include <stdio.h>
#include <dlfcn.h>
#include <iostream>
#include <stdlib.h>
#include <pthread.h>

extern int initialization_complete;


// We intend to use FrameInformation in __cyg_profile functions
// So DO NOT USE STL here
typedef unsigned int uint;
struct FrameInformation {
    public:
        uint threadid;
        uint address;
        //create a place for timestamp
        
        FrameInformation() __attribute__((no_instrument_function)) { this->threadid = 0; this->address = 0;}
        FrameInformation(int tid, int addr) __attribute__((no_instrument_function)) { this->threadid = tid; this->address = addr;}
        // One can call only such code that does not perform any 
        //    function calls or standard library calls from over here
        // One should be able to maintain a linked list or something like. No issues.
        void print () __attribute__((no_instrument_function)) { 
            // Thankfully pthread functions are not instrumentable
            // Perhaps because they are glibc functions?
            printf("In function \nthread id = %lu\n", pthread_self());
            this->threadid = pthread_self();
        }
};

#define MAX_STACK_DEPTH 200


// We intend to use Stack in __cyg_profile functions
// So DO NOT USE STL here
class Stack {
    public:
        FrameInformation frames[MAX_STACK_DEPTH];
        int index;
        Stack() __attribute__((no_instrument_function));

        void push(FrameInformation frame) __attribute__((no_instrument_function));

        FrameInformation pop() __attribute__((no_instrument_function));

        int numFrames() __attribute__((no_instrument_function));

        bool printStackFrames(const char *filename) __attribute__((no_instrument_function));

};

class FunctionTracer {
private:
    FunctionTracer();
    FunctionTracer(FunctionTracer &);
    FunctionTracer &operator = (FunctionTracer &);
public:
    static void initializeTracer();
};

#endif
