#ifndef TRACE_H
#define TRACE_H

#include <stdio.h>
#include <dlfcn.h>
#include <iostream>
#include <stdlib.h>
#include <pthread.h>



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

#define MAX_STACK_DEPTH 100

class Stack {
    public:
        Dummy frames[MAX_STACK_DEPTH];
        Stack() __attribute__((no_instrument_function)) {
            printf ("Creating stack \n");
        }

};

#endif
