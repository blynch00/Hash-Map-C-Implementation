#ifndef DYN_ARR_STRUCTS
#define DYN_ARR_STRUCTS

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

// Dynamic Array Initializations
//---------------------------------------------
// int *da_create_underlying_array(size_t);
DynArr *da_create_array(size_t);
bool da_resize_array(size_t, DynArr *);  
bool da_array_is_empty(const DynArr *);
size_t da_array_length(const DynArr *);
size_t da_array_capacity(const DynArr *);
void da_print_array(const DynArr *);
bool da_fill_array(size_t, DynArr *);
int  *da_find_minimum(DynArr *);
int *da_find_maximum(DynArr *);
bool da_append_value(int, DynArr *);
size_t da_find_value(int, DynArr *);
bool da_remove_value(int, DynArr *);
bool da_remove_at_index(size_t, DynArr *);
bool da_add_at_index(int, size_t, DynArr *);
bool da_destroy_array(DynArr *);
//------------------------------------------------

#endif