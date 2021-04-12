#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef unsigned int uint;
#define NUM_THREADS_PRIME 71

namespace FlightRecorder {
struct Node{
    uint key;
    uint hash_value;
    int idx;
    struct Node *next;
} ;

struct Bucket{
    struct Node *chain;
};

typedef struct Node Node;
typedef struct Bucket Bucket;
static int idx = -1;
pthread_mutex_t hashtable_lock;


int initializeBuckets() __attribute__((no_instrument_function));

uint hash(uint key) __attribute__((no_instrument_function));

int printHashTable() __attribute__((no_instrument_function));
 
int find(uint key) __attribute__((no_instrument_function));

int insert (uint key) __attribute__((no_instrument_function));

int getNumKeysStored() __attribute__ ((no_instrument_function));

int destroyHashtable() __attribute__ ((no_instrument_function));
}
