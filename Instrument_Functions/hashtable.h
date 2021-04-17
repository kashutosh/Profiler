#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS_PRIME 71

namespace FlightRecorder {
struct Node{
    int key;
    int hash_value;
    struct Node *next;
} ;

/**
* An array os such NUM_THREADS_PRIME buckets represents the hashtable. 
*  The Bucket node never stores any data
*
*  Bucket -> next (Node) -> next (Node) -> NULL
*  Bucket -> next (Node) -> NULL
*  Bucket -> NULL
*  Bucket -> next (Node) -> NULL
*  Bucket -> NULL
**/
struct Bucket{
    struct Node *chain;
};

typedef struct Node Node;
typedef struct Bucket Bucket;
static int idx = -1;

/** 
* All functions below are declared no_instrument_function 
* so that when called from __cyg_ functions
* these do not result in further calls
**/
int initializeBuckets() __attribute__((no_instrument_function));

// Simple hash function that yields a number
// between 0 to NUM_THREADS_PRIME-1
int hash(int key) __attribute__((no_instrument_function));

int printHashTable() __attribute__((no_instrument_function));

// find the index in which this key is hased. -1 if not found 
int find(int key) __attribute__((no_instrument_function));


// insert a key
// return -1 if it fails to insert (which must not happen)
// return the index of bucket in which the key was inserted
int insert (int key) __attribute__((no_instrument_function));

// How many keys are stored in hashtable. Could be infinity
// number of keys in NUM_THREADS_PRIME buckets
// along collision chains
int getNumKeysStored() __attribute__ ((no_instrument_function));

// Delete the keys stored in the hashtable
int destroyHashtable() __attribute__ ((no_instrument_function));

// Get the starting bucket of a collision chain
// which should be traversed
Bucket *getBucket(int index) __attribute__((no_instrument_function));


int deleteNodesRecursively(Node *node) __attribute__((no_instrument_function));
}
