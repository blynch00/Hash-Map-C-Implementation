#ifndef LLSTRUCT_H
#define LLSTRUCT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

// Struct for LinkedList; contains total size, and a pointer to the first Node within the list.
typedef struct{
    size_t size;
    Node *head;
}LinkedList;

// Struct for nodes; contain value and pointer to the next node object.
typedef struct Node {
    int value;
    struct Node *next;
}Node;


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

