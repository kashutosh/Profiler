#include "Aggregate_Stacks.h"
#include "hashtable.h"
#include <string.h>
#include <stdio.h>
#include <map>

using namespace FlightRecorder;

namespace FlightRecorder {

extern struct FrameInformation list_of_frames[];
Stack saggr;
// The key is address of a function
// The value is address of FunctionNode
std::map<void*, FunctionNode*> function_nodes;

FunctionNode::FunctionNode(void *address_, int threadid_, hrtime inclusive_time_spent_, int counter_){
    this->address = address_;
//    this->threadids.insert(threadid_);
    this->inclusive_time_spent = inclusive_time_spent_;
    this->counter = counter_;

}
bool accountFunction(void *address, int threadid, hrtime incl_time) {
    std::map<void*, FunctionNode*> :: iterator it = function_nodes.find(address);
    if (it == function_nodes.end()) {
        FunctionNode * functionNode = new FunctionNode(address, threadid, incl_time, 1);
        function_nodes.insert(std::pair<void*, FunctionNode*> (address, functionNode));
        return true;
    }
    else {

        FunctionNode * functionNode = it->second;
        functionNode->counter++;
        functionNode->inclusive_time_spent += incl_time;
//        function->threadids.insert(threadid);
        return true;
    }
}


// Identify an edge given two pointers
// Key: Description of an edge  - two pointers
// Value: Edge data
std::map<std::pair<void*, void*>, Edge*> edge_nodes;
 

Edge::Edge(void *caller_, void *callee_, int counter) {
    this->caller = caller_;
    this->callee = callee_;
    this->counter = counter;
}
bool accountEdge(void *fromaddr, void* toaddr) {
    std::pair <void*, void*>p = std::make_pair(fromaddr, toaddr);
    std::map<std::pair<void*, void*>, Edge*> :: iterator it = edge_nodes.find(p);
    if (it == edge_nodes.end()) {
        // This is a new edge
        Edge *edge = new Edge(fromaddr, toaddr, 1);
        edge_nodes.insert(std::pair<std::pair<void*, void*>, Edge*> (p, edge));
        // We do not free this edge. Leave it to somebody else for freeing
    }
    else {
        Edge *edge = it->second;
        edge->counter++;
    }
    return true;
}


bool getSignature(int threadindex, FrameInformation *node, std::string &signature) {
    // This function effectively returns signature

    std::string functioname = getFunctionName(node->address);
    int index = 0;

//    for (int i=0;i<=4;i++) {
//        printf("Stack Frame %d is %p\n", i, saggr.getFrame(i).address);
//    }

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

bool printOutTheDAG() {
    FILE * fp = fopen ("/tmp/aggr.dot", "w");

    if (fp == NULL) {
        printf("Unable to open the file to be written \n");
        return false;    
    }
    fputs("digraph { \n", fp);
    fputs("node [ shape=record ];\n", fp);
 
    // print out function nodes
    char buffer[2000];
   
    std::map<void*, FunctionNode*>::iterator itf = function_nodes.begin();
    while (itf!=function_nodes.end()) {
        FunctionNode * f = itf->second;

        Dl_info info_top;
        char top_function_name[400];
        char top_library_name[400];
        if (dladdr(f->address, &info_top)) {
            if (info_top.dli_sname) {
                strcpy(top_function_name, info_top.dli_sname);
            }
            else {
                strcpy(top_function_name, "unknown name");
            }
            if (info_top.dli_fname) {
                strcpy(top_library_name, info_top.dli_fname);
            }
            else {
                strcpy(top_library_name, "unknown library");
            }
        
        }

        sprintf(buffer, "p%p  [label=\"{Fn: %s | Time: %0.3f ms | Count: %d}\"]\n", f->address, top_function_name, f->inclusive_time_spent/(2.4*1000*1000), f->counter);
        fputs(buffer, fp);
        itf++;
    }


    // ------------------------------------------------
    std::map< std::pair<void*, void*>, Edge*>::iterator ite = edge_nodes.begin();
    while (ite!= edge_nodes.end()) {
        Edge *e = ite->second;
        sprintf(buffer, "p%p -> p%p [label=\" calls: %d \"]\n", e->caller, e->callee, e->counter);
        fputs(buffer, fp);
        ite++;
    }

    fputs("}\n", fp);
    fclose(fp);
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

                // This is the end of the stack
                // we have determined the signature for this node so far
                // check if a stack with this signature exists or not
                // so we need signature -> stack mapping
 
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

/*
                // This should never happen
                if (top_frame.threadid != d.threadid) {
                    printf("********FOUND THREAD JUMP******************\n");
                }
*/
                // We have discovered an edge from d to top_frame. Put this edge in edge_nodes
                bool edge_accounted = accountEdge(d.address, top_frame.address);
                // assert that edge_accounted is true

                // We have also found that a function has finished
                hrtime incl_time = node->end_time - top_frame.start_time;
                printf("Incl Time is %llu\n", incl_time);
                bool function_call_accounted = accountFunction(top_frame.address, top_frame.threadid, incl_time);
                saggr.pop();
            }
            node = node->next;
        }
        state = ENDSTACK;
    }
    printOutTheDAG();

}


}
