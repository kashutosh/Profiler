#include <stdio.h>
#include <stdlib.h>

typedef unsigned int uint;
#define NUM_THREADS_PRIME 11

struct Node{
    uint key;
    uint value;
    struct Node *next;
} ;

struct Bucket{
    struct Node *chain;
};

typedef struct Node Node;
typedef struct Bucket Bucket;

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
                printf("Key: %u, Value: %u\n", chain->key, chain->value);
                chain = chain->next;
            }
        }
    }
}

int insert (uint key) {
    uint hash_value = hash(key);
    // Search for this key in the hash table
    Bucket *bucket = &hashtable[hash_value];
    if (bucket->chain == NULL ){
        printf ("Found a empty bucket at %u\n", hash_value);
        Node *node = (Node *)malloc (sizeof(Node));
        node->key = key;
        node->value = hash_value;
        node->next = NULL;
        bucket->chain = node;
    }
    else {
        Node *tail= bucket->chain;
        while (tail->next != NULL) tail = tail->next;

        Node *node = (Node *)malloc (sizeof(Node));
        node->key = key;
        node->value = hash_value;
        node->next = NULL;
        tail->next = node;
 
    }
    // On insertion, return which bucket was the key inserted into
    return hash_value;
    
}

int main() {
    initializeBuckets();
    insert(10);
    insert(21);
    insert(20);
    insert(20);
    insert(31);
    insert(34);
    printHashTable();
    return 0;
}


// Ideally, we want to map tid to a number between 0-n
// 120391034 -> 0 (Key, Index)
// 120391040 -> 1
// 120391152 -> 3
