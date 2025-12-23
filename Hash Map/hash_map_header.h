#ifndef HASH_MAP_STRUCT
#define HASH_MAP_STRUCT

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "../Linked List/linked_list_header.h"


// Struct is made to take pairs and add to map
typedef struct MapNode{
    int value;
    char *key;
    struct MapNode *next;
}MapNode;

// Struct for Linked List, with MapNode as head
typedef struct{
    size_t size;
    MapNode *head;
}ArrayList;


// Struct is made to store array of linked lists; ArrayList ** is a pointer to an "array" of pointers.
typedef struct {
    size_t size;
    size_t capacity;
    ArrayList **buckets; 
}HashMap;



HashMap *hm_create_map(size_t);
size_t   hm_hash_function(char *);
bool     hm_insert_pair(int, char *, HashMap *);
bool     hm_clear_map(HashMap *);
bool     hm_resize_array(size_t, HashMap *);
size_t   hm_get_size(const HashMap *);
size_t   hm_get_capacity(const HashMap *);
bool     hm_contains_key(char *, const HashMap *);
bool     hm_contains_value(int, const HashMap *);
bool     hm_delete_map(HashMap *);
bool     hm_is_empty(const HashMap *);
bool     hm_remove(int, HashMap *);

#endif