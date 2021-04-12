#include "hashtable.h"
Bucket hashtable[NUM_THREADS_PRIME];

int initializeBuckets() {
    for (int i=0; i<NUM_THREADS_PRIME; i++) {
        hashtable[i].chain = NULL;
    }
}

uint hash(int key) {
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
}

int find(uint key) {
    // find whether the given key exists or not
    // if it exists, then return index for it
    // A find function should return index of given key
    // or return a -1 when none found

    int index_to_search = -1;

    // Find hash key and search in this hash key if this index exists

    uint hash_value = hash(key);
    Bucket *bucket = &hashtable[hash_value];
    if (bucket->chain == NULL ){
        return index_to_search;
    }
    else {
        Node *tail= bucket->chain;
        while ((tail->key != key) || (tail == NULL)) 
            tail = tail->next;
        if (tail->key == key) {
            return tail->index;
        }
    }
    return index_to_search;

}

int insert (uint key) {
    uint hash_value = hash(key);
    index++;
    // Search for this key in the hash table
    Bucket *bucket = &hashtable[hash_value];
    if (bucket->chain == NULL ){
        printf ("Found a empty bucket at %u\n", hash_value);
        Node *node = (Node *)malloc (sizeof(Node));
        node->key = key;
        node->hash_value = hash_value;
        node->index = index;
        node->next = NULL;
        bucket->chain = node;
    }
    else {
        Node *tail= bucket->chain;
        while (tail->next != NULL) tail = tail->next;

        Node *node = (Node *)malloc (sizeof(Node));
        node->key = key;
        node->hash_value = hash_value;
        node->index = index;
        node->next = NULL;
        tail->next = node;
 
    }
    // On insertion, return which bucket was the key inserted into
    return index;
    
}

int main() {
    initializeBuckets();
    int threadid;
    threadid = insert(10);
    printf("Got threadid %d for key 10 \n", threadid);
    threadid = insert(21);
    printf("Got threadid %d for key 10 \n", threadid);
    threadid = insert(20);
    printf("Got threadid %d for key 10 \n", threadid);
    threadid = insert(20);
    printf("Got threadid %d for key 10 \n", threadid);
    threadid = insert(31);
    printf("Got threadid %d for key 10 \n", threadid);
    threadid = insert(34);
    printf("Got threadid %d for key 10 \n", threadid);
    printf("find(10) = %d \n", find(10));
    printf("find(21) = %d \n", find(21));
    printf("find(20) = %d \n", find(20));
    printf("find(30) = %d \n", find(30));
    printf("find(31) = %d \n", find(31));
    printf("find(34) = %d \n", find(34));
    printf("find(35) = %d \n", find(35));
    printHashTable();
    return 0;
}


// Ideally, we want to map tid to a number between 0-n
// 120391034 -> hash_value -> 0 (Key, Index)
// 120391040 -> hash_value -> 1
// 120391152 -> hash_value -> 2

