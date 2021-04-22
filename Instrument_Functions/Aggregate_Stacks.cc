#include "Aggregate_Stacks.h"
#include "hashtable.h"
#include <string.h>
#include <stdio.h>

using namespace FlightRecorder;

namespace FlightRecorder {

extern struct FrameInformation list_of_frames[];
Stack saggr;
bool getSignature(int threadindex, FrameInformation *node, std::string &signature) {
    // This function effectively returns signature

    std::string functioname = getFunctionName(node->address);
    int index = 0;

    for (int i=0;i<=4;i++) {
        printf("Stack Frame %d is %p\n", i, saggr.getFrame(i).address);
    }

    FrameInformation current_node = saggr.getFrame(0);
    char current_node_sign[34];
    sprintf(current_node_sign, "%p|", current_node.address);
    current_node_sign[33] = 0;

    int top_of_stack = saggr.top();
    signature.append(current_node_sign);
    // One must ensure that node falls on this stack!!

    // This will not make cut to recursive functions, though ;-)
    while (current_node.address != node->address) {
         index++;
         if (index > top_of_stack) {
             return false;
         }
         printf("index is %d\n", index);
         current_node = saggr.getFrame(index);
         sprintf(current_node_sign, "%p|", current_node.address);
 
         current_node_sign[33] = '\0';
         signature.append(current_node_sign);
    }
    return true;
}

std::string getFunctionName(void *addr) {
    Dl_info info_top;
    if (dladdr(addr, &info_top)) {
        if (info_top.dli_sname) {
            printf("Getting Signature of %p: %s\n", addr, info_top.dli_sname);
            std::string s (info_top.dli_sname);
            return s;
        }
        else {
            std::string s ("unknown name");
            return s;
            //strcpy(top_function_name, "unknown name");
        }
    }
    return "";
}


bool aggregateStacks() {
    int state, prev_state;
    for (int i=0; i<NUM_THREADS_PRIME; i++) {
        // Catch the header node of each list
        FrameInformation *fptr = &list_of_frames[i];
        FrameInformation *node = fptr->next;
        if (node == NULL) continue;
        state = BEGINNING;

        printf("---------------------------------------------%d\n", i);
        printf("Processing thread %d\n", i);

        while (node!= NULL) {
            if (node->operation == PUSH) {
                prev_state = state;
                state = PUSHING;

                if (prev_state == POPPING) {
                    // I am seeing two functions being called from same call stack
                    /* foo() {
                         bar();
                         ...
                         baz();
                       }
                      When bar finishes and baz is called, POPPING -> PUSHING 
                    */ 
                }
                if (prev_state == PUSHING) {
                    // I am going deep inside callstack from foo->bar->baz
                    /*
                      foo() {
                        bar(); 
                      }
                      bar() { 
                        baz();
                      }
                    */ 
                }
                if (prev_state == ENDSTACK) {
                    // Error! You cannot push in this state
                }
                saggr.push(*node);
                printf ("*********Pushing node %s\n", getFunctionName(node->address).c_str());
            }
            else if (node->operation == POP) {
                prev_state = state;
                state =  POPPING;
                if (prev_state == PUSHING) {
                    // I am popping a frame at the tail of stack
                    // This is end of one callstack
                    std::string sign;
                    getSignature(i, node, sign);
                    printf("Signature is %s\n", sign.c_str());
                    // Put this signature in hashmap. Sum the time in that frame
                    // Finally, the hashmap represents all the stacks seen during
                    // execution of the program
                }
                if (prev_state == POPPING) {
                    // I am rewinding call stack, baz->bar->foo
                    /*
                      foo() {
                        bar(); 
                      }
                      bar() { 
                        baz();
                      }
                    */ 
 
                }
                if (prev_state == BEGINNING) {
                    // Error!! You cannot pop from this state
                }

                FrameInformation &d= saggr.getFrame(saggr.top()-1);
                FrameInformation &top_frame = saggr.getFrame(saggr.top());
                // This is the end of the stack
                // we have determined the signature for this node so far
                // check if a stack with this signature exists or not
                // so we need signature -> stack mapping
                saggr.pop();
            }
            node = node->next;
        }
        state = ENDSTACK;
    }


}


}
