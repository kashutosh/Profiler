#ifndef TRACE_H
#define TRACE_H

#include <stdio.h>
#include <dlfcn.h>
#include <iostream>
#include <stdlib.h>
#include <pthread.h>

extern int initialization_complete;
struct Dummy {
    public:
        int data;
        int array[10];
        int counter;
        unsigned long int threadid;
        Dummy() __attribute__((no_instrument_function)) { this->counter=0;}
        // One can call only such code that does not perform any 
        //    function calls or standard library calls from over here
        // One should be able to maintain a linked list or something like. No issues.
        void print () __attribute__((no_instrument_function)) { 
            counter++;
            if (counter>=9) counter=0;
            printf("Dummy data is %d\n", data); 
            array[counter]= data; 
            // Thankfully pthread functions are not instrumentable
            // Perhaps because they are glibc functions?
            printf("In function \nthread id = %lu\n", pthread_self());
            this->threadid = pthread_self();
        }
};

#define MAX_STACK_DEPTH 200

class Stack {
    public:
        Dummy frames[MAX_STACK_DEPTH];
        int index;
        Stack() __attribute__((no_instrument_function)) {
            printf ("Creating stack \n");
            index = -1;
        }

        void push(Dummy frame) __attribute__((no_instrument_function)) {
            index++;
            frames[index] = frame;
        }

        Dummy pop() __attribute__((no_instrument_function)) {
            Dummy d;
            // When main is exited, event then pop is called
            // So is case when main entered
            // if (index <= 0) return d;
            d = frames[index];
            index--;
            return d;
        }

        int numFrames() __attribute__((no_instrument_function)) {
            return index;
        }

};

#endif
