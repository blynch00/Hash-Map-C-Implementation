#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "hash_map_header.h"


int main(void){
    HashMap *new_map = hm_create_map(4);

    return 0;
}

/*
Function: create_map
Purpose: creation of HashMap object
Params: size_t capacity
Returns: HashMap pointer
*/
HashMap *hm_create_map(size_t capacity){
    if(capacity == 0) capacity = 4;

    HashMap *new_map = malloc(sizeof(HashMap));
    if(!new_map){
        fprintf(stderr, "Error: create_map malloc allotment returned NULL.\n");
        return NULL;
    }
    ArrayList **new_buckets = calloc(capacity, sizeof(ArrayList));
    if(!new_buckets){
        fprintf(stderr, "Error: Calloc returned NULL during buckets creation. \n");
        return NULL;
    }
    new_map->size = 0;
    new_map->capacity = capacity;
    new_map->buckets = new_buckets;
    return new_map;
}



/*
Function: hash_function
Purpose: returns integer, as the index of the array in which to insert the new key/value pair.
Params:  char *key
Returns: size_t index
*/
size_t hm_hash_function(char *key){
    // djb2?
    return 0;

}
      

/*
Function: insert_pair
Purpose: inserts hash_map (key, value) into HashMap
Params:  int value, char *key, HashMap pointer
Returns: boolean, dependent on insertion
*/
bool hm_insert_pair(int value, char *key, HashMap *map){
    // Malloc for size of MapNode
    MapNode *new_node = malloc(sizeof(MapNode));
    if(!new_node){
        fprintf(stderr, "Error: Malloc returned NULL during node creation.\n");
        return false;
    }
    new_node->value = value;
    new_node->key = key;
    
    //size_t index = hm_hash_function(key);
    
    // insert new_node into map->buckets[index]

    // increment size

    // calculate load factor

    // Call resize_array if needed.


    return false;
}



/*
Function: clear_map
Purpose:  removes (frees) all key-value pairs within map.
Params:   HashMap pointer
Returns:  boolean
*/
bool hm_clear_map(HashMap *map){
    // Iterate through each bucket, finding individual size, then free(node)
    return true;
}



/*
Function: resize_array
Purpose:  resizes array size
Params:   size_t capacity, HashMap pointer
Returns:  boolean
*/
bool hm_resize_array(size_t capacity, HashMap *map){
    // Use realloc, or if (!map->buckets) create new array(?)
    // Create new array, moving all key/value pairs over, or delete each node and create a new one at the new_array.
    return false;
}
/*
Function: get_size
Purpose: returns current # of key/values within map.
Params:  HashMap pointer
Returns: size_t size
*/
size_t hm_get_size(const HashMap *map){
    return map->size;
}



/*
Function: get_capacity
Purpose:  returns the total length of the array, i.e. total number of list pointers stored.
Params:   HashMap pointer
Returns:  size_t capacity
*/
size_t hm_get_capacity(const HashMap *map){
    return map ->capacity;
}



/*
Function: contains_key
Purpose:  checks whether or not the current HashMap contains the given key 
Params:   char *key, HashMap pointer
Returns:  boolean
*/
bool hm_contains_key(char *key, const HashMap *map){
    return false;
}



/*
Function: contains_value
Purpose:  checks whether the current HashMap is storing the given integer
Params:   int value, HashMap pointer
Returns:  boolean
*/
bool hm_contains_value(int value, const HashMap *map){
    return false;
}


/*
Function: is_empty
Purpose: returns whether or not the map is empty, as a boolean.
Params:  HashMap pointer
Returns: boolean
*/
bool hm_is_empty(const HashMap *map){
    // if map->size != 0, return false
    // check each linked list heads, if any is not NULL, return false
    return (true);
}


/*
Function: remove
Purpose: Given an integer, removes the value, if present, from the HashMap
Params:  int value, HashMap pointer
Returns: boolean
*/
bool hm_remove(int value, HashMap *map){
    return false;
}

/*
Function: delete_map
Purpose:  HashMap deletion; deletes all key/value pairs, then the internal pointer "array", then the struct in memory.
Params:   HashMap pointer
Returns:  boolean
*/
bool hm_delete_map(HashMap *map){
    // call clear_map, then free(map)
    return false;
}