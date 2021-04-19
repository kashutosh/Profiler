#ifndef TRACE_H
#define TRACE_H

#include <stdio.h>
#include <dlfcn.h>
#include <iostream>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define PUSH 1
#define POP 0
#define UNDEFINED -1

extern int initialization_complete;


// We intend to use FrameInformation in __cyg_profile functions
// So DO NOT USE STL here
typedef unsigned long long int hrtime;
#define MAX_NAME_LEN 400
#define MAX_LIBNAME_LEN 200


// What information is pushed on stack when __cyg function is called?

struct FrameInformation {
        int threadid;
        void *address;
        void *call_site; 
        hrtime start_time;
        hrtime end_time;
        int id;
        int operation; // 1 = PUSH, 0 = POP
        FrameInformation *next;
        //create a place for timestamp
        
        FrameInformation(int threadid_ = 0, 
                         void *address_ = 0, 
                         void* call_site_ = 0, 
                         hrtime start_time_ = 0, 
                         hrtime end_time_ = 0,
                         const int id_ = 0,
                         int operation = UNDEFINED ) __attribute__((no_instrument_function)) { 
            this->threadid = threadid_; 
            this->address = address_;
            this->call_site = call_site_;
            this->start_time = start_time_;
            this->end_time = end_time_;
            this->id = id_;
            this->operation = operation;
        }
        // One can call only such code that does not perform any 
        //    function calls or standard library calls from over here
        // One should be able to maintain a linked list or something like. No issues.
        void print () __attribute__((no_instrument_function)) { 
            // Thankfully pthread functions are not instrumentable
            // Perhaps because they are glibc functions?
            printf("------------------------------------------\n");
            printf("threadid: %u , address: %p, call_site: %p, start_time: %llu \n", threadid, address, call_site, start_time);
            printf("------------------------------------------\n");
            
        }
};


// MAX_STACK_DEPTH is defined to be 200
// In real life, most code will not have this much of a deep stack

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


#endif
