#ifndef AGGREGATE_STACKS_H
#define AGGREGATE_STACKS_H
#include <string>
#include <vector>
#include <map>
#include <set>
#include "Trace.h"

namespace FlightRecorder {

#define BEGINNING 98
#define PUSHING 99
#define POPPING 100
#define ENDSTACK 101
typedef unsigned long long int hrtime;

    // Algorithm 1:
    // Keep a mapping from address -> time spent
    // wherever a function is shown, show the aggregate time spent in that function
    // create one node for each function and create a DAG

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
         hrtime time_spent; // Time is associated with the function at the bottom of the callstack 
                            // We might not be able to store it
    };

    struct FunctionNode {
        void * address;
        std::set<int> threadids;
        int counter;
        hrtime inclusive_time_spent;
        hrtime exclusive_time_spent;
        FunctionNode(void *address_, int threadid_, hrtime inclusive_time_spent_, int counter_);
        private:
            FunctionNode();
    };

    struct Edge {
        void *caller;
        void *callee;
        int counter;
        Edge(void *caller_, void *callee, int counter=0);
        private:
            Edge();
    };

  

bool getSignature(int threadindex, FrameInformation *node, std::string &signature);
std::string getFunctionName(void *addr);
bool aggregateStacks();
}
#endif
