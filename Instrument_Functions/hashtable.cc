#include "hashtable.h"

namespace FlightRecorder {
static Bucket hashtable[NUM_THREADS_PRIME];

pthread_mutex_t hashtable_lock;
int initializeBuckets() {
    printf("Initializing buckets \n");
    for (int i=0; i<NUM_THREADS_PRIME; i++) {
        hashtable[i].chain = NULL;
    }
    return 0;
}

uint hash(uint key) {
    return key%NUM_THREADS_PRIME;
}

int printHashTable() {
    printf("Printing hashtable \n");
    for (int i=0; i<NUM_THREADS_PRIME; i++) {
        Node *chain = hashtable[i].chain;
        if (chain != NULL ) {
            printf("Found an non-empty bucket at %d\n", i);
            while (chain!= NULL) {
                printf("Key: %u, Value: %u\n", chain->key, chain->hash_value);
                chain = chain->next;
            }
        }
    }
    return 0;
}

int find(uint key) {
    // find whether the given key exists or not
    // if it exists, then return idx for it
    // A find function should return idx of given key
    // or return a -1 when none found

    int idx_to_search = -1;

    // Find hash key and search in this hash key if this idx exists

    uint hash_value = FlightRecorder::hash(key);
    printf("hash_value is %u\n", hash_value);
    Bucket *bucket = &hashtable[hash_value];
    if (bucket->chain == NULL ){
        return idx_to_search;
    }
    else {
        Node *tail= bucket->chain;
        while ((tail->key != key) || (tail == NULL)) 
            tail = tail->next;
        if (tail->key == key) {
            return tail->idx;
        }
    }
    return idx_to_search;

}

int insert (uint key) {
    uint hash_value = FlightRecorder::hash(key);

    pthread_mutex_lock(&hashtable_lock);
    // When inserting, always do a find first and iff it returns
    // false, then only insert. Otherwise return
    
    int found_idx = FlightRecorder::find(key);
    if (found_idx != -1) {
        pthread_mutex_unlock(&hashtable_lock);
        return found_idx;
    }
    idx++;
    // Search for this key in the hash table
    Bucket *bucket = &hashtable[hash_value];
    if (bucket->chain == NULL ){
        printf ("Found a empty bucket at %u\n", hash_value);
        Node *node = (Node *)malloc (sizeof(Node));
        node->key = key;
        node->hash_value = hash_value;
        node->idx = idx;
        node->next = NULL;
        bucket->chain = node;
    }
    else {
        Node *tail= bucket->chain;
        while (tail->next != NULL) tail = tail->next;

        Node *node = (Node *)malloc (sizeof(Node));
        node->key = key;
        node->hash_value = hash_value;
        node->idx = idx;
        node->next = NULL;
        tail->next = node;
 
    }
    // On insertion, return which bucket was the key inserted into
    pthread_mutex_unlock(&hashtable_lock);
    return idx;
    
}
int getNumKeysStored() {
    int counter = 0;
    for (int i=0; i<NUM_THREADS_PRIME; i++) {
        Node *chain = hashtable[i].chain;
        if (chain != NULL ) {
            while (chain!= NULL) {
                chain = chain->next;
                counter++;
            }
        }
    }
    return counter;
}

int destroyHashtable() {
    pthread_mutex_lock(&hashtable_lock);
    // Go on freeing up nodes allocated. Err, how?
    pthread_mutex_unlock(&hashtable_lock);
    return 0;
}


}

/*
int main() {
    FlightRecorder::initializeBuckets();
    int threadid;
    threadid = FlightRecorder::insert(10);
    printf("Got threadid %d for key 10 \n", threadid);
    threadid = FlightRecorder::insert(21);
    printf("Got threadid %d for key 10 \n", threadid);
    threadid = FlightRecorder::insert(20);
    printf("Got threadid %d for key 10 \n", threadid);
    threadid = FlightRecorder::insert(20);
    printf("Got threadid %d for key 10 \n", threadid);
    threadid = FlightRecorder::insert(31);
    printf("Got threadid %d for key 10 \n", threadid);
    threadid = FlightRecorder::insert(34);
    printf("Got threadid %d for key 10 \n", threadid);
    printf("find(10) = %d \n", FlightRecorder::find(10));
    printf("find(21) = %d \n", FlightRecorder::find(21));
    printf("find(20) = %d \n", FlightRecorder::find(20));
    printf("find(30) = %d \n", FlightRecorder::find(30));
    printf("find(31) = %d \n", FlightRecorder::find(31));
    printf("find(34) = %d \n", FlightRecorder::find(34));
    printf("find(35) = %d \n", FlightRecorder::find(35));
    FlightRecorder::printHashTable();
    return 0;
}

*/

// Ideally, we want to map tid to a number between 0-n
// 120391034 -> hash_value -> 0 (Key, Index)
// 120391040 -> hash_value -> 1
// 120391152 -> hash_value -> 2

