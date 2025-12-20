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
        int *minimum;
        int *maximum;
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


// Dynamic Array Initializations
//---------------------------------------------
int *da_create_underlying_array(size_t);
DynArr da_create_DynArr(size_t);
bool da_resize_array(size_t, DynArr *);  
bool da_array_is_empty(DynArr *);
size_t da_array_length(DynArr *);
size_t da_array_capacity(DynArr *);
void da_print_array(DynArr *);
void da_fill_array(size_t, DynArr *);
bool da_find_minimum(DynArr *);
bool da_find_maximum(DynArr *);
void da_append_value(int, DynArr *);
size_t da_find_value(int, DynArr *);
void da_remove_value(int, DynArr *);
void da_remove_at_index(size_t, DynArr *);
void da_add_at_index(int, size_t, DynArr *);
void da_update_min_max(int, DynArr *);
void da_find_min_max(DynArr *);
//------------------------------------------------

//--------------------- Linked List Initializations ---------------------------
LinkedList *create_list(void);
int ll_get_size(LinkedList *);
struct Node *ll_get_head(LinkedList *);
Node *ll_get_node_by_value(int,LinkedList *);
int ll_add_value(int, LinkedList *);
void ll_fill_list(int, LinkedList *);
void ll_print_list(LinkedList *);
int ll_delete_value(int, LinkedList *);
int ll_delete_node(Node *,  LinkedList *);
int ll_clear_list(LinkedList *);
bool ll_list_is_empty(LinkedList *);
bool ll_contains(int, LinkedList *);
int ll_index_of_value(int, LinkedList *);
//------------------------------------------------


#endif