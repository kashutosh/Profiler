#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//typedef int int;
#define NUM_THREADS_PRIME 71

namespace FlightRecorder {
struct Node{
    int key;
    int hash_value;
    struct Node *next;
} ;

struct Bucket{
    struct Node *chain;
};

typedef struct Node Node;
typedef struct Bucket Bucket;
static int idx = -1;


int initializeBuckets() __attribute__((no_instrument_function));

int hash(int key) __attribute__((no_instrument_function));

int printHashTable() __attribute__((no_instrument_function));
 
int find(int key) __attribute__((no_instrument_function));

int insert (int key) __attribute__((no_instrument_function));

int getNumKeysStored() __attribute__ ((no_instrument_function));

int destroyHashtable() __attribute__ ((no_instrument_function));

Bucket *getBucket(int index) __attribute__((no_instrument_function));
}
