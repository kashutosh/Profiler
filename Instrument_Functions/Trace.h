#ifndef TRACE_H
#define TRACE_H

#include <stdio.h>
#include <dlfcn.h>
#include <iostream>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

extern int initialization_complete;


// We intend to use FrameInformation in __cyg_profile functions
// So DO NOT USE STL here
//typedef int uint;
typedef long int ulint;
typedef unsigned long long int hrtime;
#define MAX_NAME_LEN 200
struct FrameInformation {
    public:
        uint threadid;
        void *address;
        void *call_site; 
        hrtime start_time;
        hrtime end_time;
        char function_name[MAX_NAME_LEN];
        //create a place for timestamp
        
        FrameInformation(uint threadid_ = 0, 
                         void *address_ = 0, 
                         void* call_site_ = 0, 
                         hrtime start_time_ = 0, 
                         hrtime end_time_ = 0,
                         const char *function_name_ = NULL) __attribute__((no_instrument_function)) { 
            this->threadid = threadid_; 
            this->address = address_;
            this->call_site = call_site_;
            this->start_time = start_time_;
            this->end_time = end_time_;
            strcpy(this->function_name, function_name);
        }
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

        int top() __attribute__((no_instrument_function)); 

        FrameInformation &getFrame(int index) __attribute__((no_instrument_function));

};

class FunctionTracer {
private:
    FunctionTracer();
    FunctionTracer(FunctionTracer &);
    FunctionTracer &operator = (FunctionTracer &);
public:
    static FILE *fp;
    static bool initializeTracer();
    static bool stopTracer();
};

#endif
