#include "Trace.h"
#include "hashtable.h"
#include "LinkedListOfFrames.h"
#include "FunctionTracer.h"
#include <cxxabi.h>
#include <string>

extern FlightRecorder::Hashtable h;
namespace FlightRecorder {
// One must have a bunch of lists, one for each thread!!
struct FrameInformation list_of_frames[NUM_BUCKETS_PRIME];
struct FrameInformation *tails[NUM_BUCKETS_PRIME];



void initializeLinkedLists() {
    for (int i=0; i<NUM_BUCKETS_PRIME; i++) {
        list_of_frames[i].next = NULL;
    }
    for (int i=0; i<NUM_BUCKETS_PRIME; i++) {
        //Initially, this points to header node only 
        // Tail should be initialized to where the last node is, which 
        // for initialization is header node
        tails[i] = &list_of_frames[i];
    }
}

FrameInformation *getFrame(int index) {
    if (index<0 || index>= NUM_BUCKETS_PRIME) return NULL;
    return &list_of_frames[index];
}

FrameInformation *getTail(int index) {
    if (index<0 || index>= NUM_BUCKETS_PRIME) return NULL;
    return tails[index];
}


bool appendNodeToTailOfAList(FrameInformation *node, int index) {
    // No lock should be required on this function
    FrameInformation *tail = tails[index];
    if (tail == NULL) {
        return false;
    }
    tail->next = node;
    node->next = NULL;

    // tail should now point to the last node
    tails[index] = node;
    return true;
}


float getTimeInMSFromTraceBeginning(hrtime current_time) {
    return (current_time - FunctionTracer::execution_start_time) / (FunctionTracer::clock_speed*1000*1000);
}

Stack sprint;

bool printTheListsOutToAFile() {
    int idx;
    char buffer[2000];
    char buffertext[2000];
    int tablevel = 0;
    for (int i=0; i<NUM_BUCKETS_PRIME; i++) {
        // Catch the header node of each list
        FrameInformation *fptr = &list_of_frames[i];
        // There is no information in the header node itself. Start traversing the list
        FrameInformation *node = fptr->next;
        if (node == NULL) continue;
//        printf("Printing out - non zero - list number %d\n", i);

        int pushcounter =0, popcounter =0;
        while (node!= NULL) {
            if (node->operation == PUSH) {
                // One day we will see POP for this
                // Push this node on Stack!! This is the only way we can compute time spent in this function
//                printf("LL:Pushing node %d Addr: %p\n", node->id, node->address);
                pushcounter++;
                sprint.push(*node);
                tablevel++;

                for (int t=0; t<tablevel; t++) {
                    sprintf(buffertext+(t*4), "----");
                }

                fputs(buffertext, FunctionTracer::fptext);

                Dl_info info_top;
                char top_function_name[400];
                char top_library_name[400];
                // Decode this address
                if (dladdr(node->address, &info_top)) {
//                    printf("POP: [%s] ",info_top.dli_sname ? info_top.dli_sname : "unknown");
//                    printf("POP: [%s]\n",info_top.dli_fname ? info_top.dli_fname : "unknown");
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
                int status;
                sprintf(buffertext, "TS: %.3f ms, Thread: %d, CallID: %u, %s\n", getTimeInMSFromTraceBeginning
(node->start_time), node->threadid, node->id, abi::__cxa_demangle(top_function_name, 0, 0, &status));
                fputs(buffertext, FunctionTracer::fptext);
            }
            else if (node->operation == POP) {
//                printf("LL:Popping node %d Addr: %p\n", node->id, node->address);
                FrameInformation &d= sprint.getFrame(sprint.top()-1);
                FrameInformation &top_frame = sprint.getFrame(sprint.top());

                sprintf(buffer, " p%d -> p%d [label=\"%d\"] \n", d.id, top_frame.id, top_frame.id);
                fputs(buffer, FunctionTracer::fp);

                
                void *top_frame_addr = top_frame.address;
                Dl_info info_top;
                char top_function_name[400];
                char top_library_name[400];
                // Decode this address
                if (dladdr(top_frame_addr, &info_top)) {
//                    printf("POP: [%s] ",info_top.dli_sname ? info_top.dli_sname : "unknown");
//                    printf("POP: [%s]\n",info_top.dli_fname ? info_top.dli_fname : "unknown");
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

                int status;
                sprintf(buffer, " p%d [label= \"{%s | Threadid: %u | Time: %.3f ms| Lib: %s }\" ];\n", top_frame.id, abi::__cxa_demangle(top_function_name, 0, 0, &status), top_frame.threadid, (node->end_time-top_frame.start_time)/FunctionTracer::clock_speed/1000/1000, top_library_name);
                fputs(buffer, FunctionTracer::fp);


                idx = ::h.find(top_frame.threadid);
            
                if (idx == -1 ) {
                    printf("Found that threadid %d does not exist in hashtable when popping a frame\n", top_frame.threadid);
                    node = node->next;
                    continue;
                }

                sprint.pop();
                popcounter++;
                tablevel--;
            }
            node = node->next;
        }
        printf("I did %d PUSH and %d POPs \n", pushcounter, popcounter);
    }
}




int deleteNodesInLinkedListRecursively(FrameInformation *node) {
    int count = 0;
    if (node->next != NULL) {
        count = deleteNodesInLinkedListRecursively(node->next);
    }
    free(node);
    return count+1;
}


void cleanupLinkedLists() {
    int total_nodes_deleted = 0;
    for (int i=0; i<NUM_BUCKETS_PRIME; i++) {
        FrameInformation *chain = list_of_frames[i].next;
        // chain is the first node on the list
        if (chain != NULL ) {
            int count = deleteNodesInLinkedListRecursively(chain);
            total_nodes_deleted += count;
        }
        chain->next = NULL;
    }
    printf("Total nodes deleted are %d\n", total_nodes_deleted);
    //hashtable_idx = -1;
    initializeLinkedLists();
}

}
