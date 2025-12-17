#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

// Struct for Dynamic Array (basic); contains size, capacity, and pointer to array 
typedef struct{
        size_t size;
        size_t capacity;
        int *items;
    }DynArr;

// Struct for nodes; contain value and pointer to the next node object.
typedef struct Node {
    int value;
    struct Node *next;
}Node;

// Struct for LinkedList; contains total size, and a pointer to the first Node within the list.
typedef struct{
    size_t size;
    Node *head;
}LinkedList;

#endif