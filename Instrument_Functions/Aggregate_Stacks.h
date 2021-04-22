#ifndef AGGREGATE_STACKS_H
#define AGGREGATE_STACKS_H
#include <string>
#include <vector>
#include <map>
#include "Trace.h"

namespace FlightRecorder {

#define BEGINNING 98
#define PUSHING 99
#define POPPING 100
#define ENDSTACK 101
typedef unsigned long long int hrtime;

    struct HashtableOfStacks {

    };


    // When we see PUSH->POP, it means we have seen tail of the stack
    // At that point of time, whole call stack is available to sum up time spents?
    // Each pop operation specifies one function call end and time spent in it

    // Can we create one node per function?
    struct CallStack {
         // Simply said, signature is concat of all addresses 
         // on the call stack
         std::string signature;
         // If a callstack is seen many times, simply
         // increment occurrence count and aggregate time spent in it
         // However, this will only allow summing up time across entire callstack
         // Not in individual functions
         int occurrence_count;
         hrtime time_spent;
    };
   

bool getSignature(int threadindex, FrameInformation *node, std::string &signature);
std::string getFunctionName(void *addr);
bool aggregateStacks();
}
#endif
