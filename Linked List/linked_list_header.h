#ifndef LLSTRUCT_H
#define LLSTRUCT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>


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

//--------------------- Linked List Initializations ---------------------------
LinkedList *ll_create_list(void);
size_t ll_get_size(const LinkedList *);
struct Node *ll_get_head(const LinkedList *);
Node *ll_get_node_by_value(int,const LinkedList *);
bool ll_add_value(int, LinkedList *);
void ll_fill_list(int, LinkedList *);
void ll_print_list(const LinkedList *);
bool ll_delete_value(int, LinkedList *);
bool ll_delete_node(Node *,  LinkedList *);
bool ll_clear_list(LinkedList *);
bool ll_list_is_empty(const LinkedList *);
bool ll_contains(int, const LinkedList *);
size_t ll_index_of_value(int, const LinkedList *);
bool ll_delete_list(LinkedList *);
//------------------------------------------------


#endif

