#include "hashtable.h"

namespace FlightRecorder {
//Notice that this is a global hashtable,
// limited by its namespace only. Requires C++

static Bucket hashtable[NUM_THREADS_PRIME];
// This lock is to be used only when modifying the hashtable
// which is very rare anyway
pthread_mutex_t hashtable_lock;

int initializeBuckets() {
    printf("Initializing buckets \n");
    for (int i=0; i<NUM_THREADS_PRIME; i++) {
        hashtable[i].chain = NULL;
    }
    return 0;
}

Bucket *getBucket(int index) {
    if (index > NUM_THREADS_PRIME || index <0) return NULL;
    return &hashtable[index];
}

// abs is used to convert -ve numbers to +ve
// earlier, uints were used but they are quite 
// tricky to handle
int hash(int key) {
    return abs(key%NUM_THREADS_PRIME);
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

int find(int key) {

    // Find hash key and search in this hash key if this idx exists

    int hash_value = FlightRecorder::hash(key);
    printf("hash value for %d is %u\n", key, hash_value);
    Bucket *bucket = &hashtable[hash_value];
    if (bucket->chain == NULL ){
        printf("find is returning -1 for key=%d, hash_value=%d\n", key, hash_value);
        return -1;
    }
    else {
        Node *tail= bucket->chain;
        printf("First node's value is %d\n", tail->key);
        while (tail != NULL) {
            if (tail->key == key ) {
                printf("Found the key at %d\n", tail->key);
                return hash_value;
            }
            tail = tail->next;
        }
   }
    return -1;

}

int insert (int key) {
    int hash_value = FlightRecorder::hash(key);

    pthread_mutex_lock(&hashtable_lock);
    // When inserting, always do a find first and iff it returns
    // false, then only insert. Otherwise return
    
    int found_idx = FlightRecorder::find(key);
    if (found_idx != -1) {
        printf ("Found that the key was already inserted at %u\n", found_idx);
        pthread_mutex_unlock(&hashtable_lock);
        return found_idx;
    }
    // Search for this key in the hash table
    Bucket *bucket = &hashtable[hash_value];
    if (bucket->chain == NULL ){
        printf ("Found a empty bucket at %u\n", hash_value);
        Node *node = (Node *)malloc (sizeof(Node));
        node->key = key;
        node->hash_value = hash_value;
        node->next = NULL;
        bucket->chain = node;
    }
    else {
        printf ("Found a non-empty bucket at %u\n", hash_value);
        // When we enter here, we must necessarily have found = false, isn't it?
        Node *tail= bucket->chain;
        while (tail->next != NULL) tail = tail->next;

        Node *node = (Node *)malloc (sizeof(Node));
        node->key = key;
        node->hash_value = hash_value;
        node->next = NULL;
        tail->next = node;
    }
    // On insertion, return which bucket was the key inserted into
    pthread_mutex_unlock(&hashtable_lock);
    return hash_value;
    
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
    int total_nodes_deleted = 0;
    // Go on freeing up nodes allocated. Err, how?
    for (int i=0; i<NUM_THREADS_PRIME; i++) {
        Node *chain = hashtable[i].chain;
        // chain is the first node on the list
        if (chain != NULL ) {
            int count = deleteNodesRecursively(chain);
            total_nodes_deleted += count;
        }
        hashtable[i].chain = NULL;
    }
    printf("Total nodes deleted are %d\n", total_nodes_deleted);

    pthread_mutex_unlock(&hashtable_lock);
    return 0;
}

int deleteNodesRecursively(Node *node) {
    int count = 0;
    if (node->next != NULL) {
        count = deleteNodesRecursively(node->next);
    }
    free(node);
    return count+1;
}

}


