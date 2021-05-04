#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_BUCKETS_PRIME 71

namespace FlightRecorder {

struct Hashtable {
struct Node{
    int key;
    int hash_value;
    int idx;
    struct Node *next;
} ;

/**
* An array os such NUM_BUCKETS_PRIME buckets represents the hashtable. 
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
int hashtable_idx;


//Notice that this is a global hashtable,
// limited by its namespace only. Requires C++

Bucket hashtable[NUM_BUCKETS_PRIME];

// This lock is to be used only when modifying the hashtable
// which is very rare anyway
pthread_mutex_t hashtable_lock;



/** 
* All functions below are declared no_instrument_function 
* so that when called from __cyg_ functions
* these do not result in further calls
**/
int initializeBuckets() __attribute__((no_instrument_function));

// Simple hash function that yields a number
// between 0 to NUM_BUCKETS_PRIME-1
int hash(int key) __attribute__((no_instrument_function));

int printHashTable() __attribute__((no_instrument_function));

// find the index in which this key is hased. -1 if not found 
int find(int key) __attribute__((no_instrument_function));


// insert a key
// return -1 if it fails to insert (which must not happen)
// return the index of bucket in which the key was inserted
int insert (int key) __attribute__((no_instrument_function));

// How many keys are stored in hashtable. Could be infinity
// number of keys in NUM_BUCKETS_PRIME buckets
// along collision chains
int getNumKeysStored() __attribute__ ((no_instrument_function));

// Delete the keys stored in the hashtable
int destroyHashtable() __attribute__ ((no_instrument_function));

// Get the starting bucket of a collision chain
// which should be traversed
Bucket *getBucket(int index) __attribute__((no_instrument_function));


int deleteNodesRecursively(Node *node) __attribute__((no_instrument_function));
}; // end struct

}
