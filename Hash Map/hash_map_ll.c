#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "hash_map_header.h"
#include <ctype.h>          // used in hash_function

int main(void){
    HashMap *new_map = hm_create_map(4);
    
    char *name = "Finnegan";
    char *age  = "Twenty-Four-Eighteen_19922";
    char *test = "1a";
    size_t name_index = hm_hash_function(name, new_map);
    size_t age_index  = hm_hash_function(age, new_map);
    size_t test_index = hm_hash_function(test, new_map);
    if(name_index > 3 || age_index > 3){
        fprintf(stderr, "Indexes out of range\n");
        return 1;
    }
    printf("Size: %zu, Capacity: %zu\n", hm_get_size(new_map), hm_get_capacity(new_map));
    printf("Name index: %zu, Age index: %zu, test index: %zu\n", name_index, age_index, test_index);
    hm_print_map(new_map);
    printf("\n----------\n");
    if(!hm_insert_pair(22, name, new_map)){
        fprintf(stderr, "Error: pair could not be inserted in main.");
        return 1;
    }
    if(!hm_insert_pair(12,test,new_map)){
        fprintf(stderr, "Error: pair could not be inserted.\n");
        return 1;
    }
    hm_print_map(new_map);
    printf("\n----------\n");
    hm_resize_array(6, new_map);
    hm_print_map(new_map);
    char *example_name = "Binnegan";
    printf("Size: %zu, Capacity: %zu\n", hm_get_size(new_map), hm_get_capacity(new_map));
    //printf("Contains Finnegan: %s\n", hm_contains_key(name, new_map)? "true": "false");
    //printf("Contains Binnegan: %s\n", hm_contains_key(example_name, new_map)? "true": "false");
    if(!hm_remove_key(name, new_map)){
        fprintf(stderr, "Error- node could not be removed.\n");
        return 0;
    }
    printf("Removed value: 22\n");
    hm_print_map(new_map);
    printf("Size: %zu, Capacity: %zu\n", hm_get_size(new_map), hm_get_capacity(new_map));
    printf("Map Deleted: %s\n", hm_delete_map(new_map)? "true":"false");
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
    // Malloc for total size of struct
    HashMap *new_map = malloc(sizeof(HashMap));
    if(!new_map){
        fprintf(stderr, "Error: create_map malloc allotment returned NULL.\n");
        return NULL;
    }
    // Calloc for component storing list pointers; create an array of individual ArrayList structs
    ArrayList **new_buckets = calloc(capacity, sizeof(ArrayList *));
    if(!new_buckets){
        fprintf(stderr, "Error: Calloc returned NULL during buckets creation. \n");
        return NULL;
    }
    for(size_t x = 0; x < capacity; ++x){
        ArrayList *sublist = malloc(sizeof(ArrayList));

        if(!sublist){
            fprintf(stderr, "Error: malloc returned NULL during sublist creation.\n");
            return NULL;
        }
        sublist->head = NULL;
        sublist->size = 0;
        new_buckets[x] = sublist;

    }
    // Only changes member values if both malloc & calloc return non-NULL pointers
    new_map->size = 0;
    new_map->capacity = capacity;
    new_map->buckets = new_buckets;
    printf("New map created.\n");
    return new_map;
}



/*
Function: hash_function
Purpose: returns integer, as the index of the array in which to insert the new key/value pair.
Params:  char *key
Returns: size_t index
*/                                                  // MUST REWORK
size_t hm_hash_function( const char *key, HashMap *map){
    // djb2?
    unsigned int hash = 5381;
    int c;
    while ((c = *key++)){
        if(isupper(c))
        {
            c += 32;
        }
        hash = ((hash << 5) + hash) + c;
    }
    return (size_t) hash % map->capacity;

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
    new_node->next = NULL;
    
    // Find index
    size_t index = hm_hash_function(key, map);

    // insert new_node into map->buckets[index]
    if (map->buckets[index]->head == NULL){
        map->buckets[index]->head = new_node;
        map->size++;
    }
    else{
        new_node->next = map->buckets[index]->head;
        map->buckets[index]->head = new_node;
        map->size++;     
    }

    // calculate load factor
    if(map->size / map->capacity >= 1.0){
        printf("Must resize.\n");
    }
    // Call resize_array if needed.

    return true;
}

/*
Function: print_map
Purpose:  if elements are stored within hash map, prints them.
Params:   HashMap pointer
Returns:  void (prints via stdout stream)
*/
void hm_print_map(HashMap *map){
    if(!map || map->capacity == 0) return;

    for(size_t x = 0; x < map->capacity; ++x){
        // For each list in the array:
        // printf("\nx\n");
        
        if(map->buckets[x]->head == NULL){
            if( x +1 == map->capacity){
                printf("X\n");
                continue;
            }
            printf("X\n|\n");
            continue;
        }
        else{
            MapNode *current_node = map->buckets[x]->head;
            while(current_node){
                printf("%d --> ", current_node->value);
                current_node = current_node->next;
            }
            printf(" X \n|\n");
            continue;
        }
    }

}

/*
Function: clear_map
Purpose:  removes (frees) all key-value pairs within map.
Params:   HashMap pointer
Returns:  boolean
*/
bool hm_clear_map(HashMap *map){
    // Iterate through each bucket, finding individual size, then free(node)
    if(!map) return false;

    for(size_t x = 0; x < map->capacity; ++x){
        if (map->buckets[x]->head == NULL) continue;
 
        MapNode *current_node = map->buckets[x]->head;
        while(current_node->next != NULL){
            // Must save as variable before, so we know the next node to free.
            MapNode *next_node = current_node->next;
            free(current_node);
            current_node = next_node;
        }
        free(current_node);
        map->buckets[x]->head = NULL;
        //
    }
    return true;
}



/*
Function: resize_array
Purpose:  resizes array size
Params:   size_t capacity, HashMap pointer
Returns:  boolean
*/
bool hm_resize_array(size_t new_capacity, HashMap *map){
    if(!map){
        fprintf(stderr, "Error- failure to pass map to resize_array.\n");
        return false;
    }
    
    // If the load factor is too large, resize capacity.
    if( ((double)map->size / new_capacity) >= 1.0) new_capacity *= 2;

    ArrayList **new_buckets = calloc(new_capacity, sizeof(ArrayList *));
    if(!new_buckets){
        fprintf(stderr, "Error: Calloc returned NULL during resize. \n");
        return NULL;
    }
    for(size_t x = 0; x < new_capacity; ++x){
        ArrayList *sublist = malloc(sizeof(ArrayList));
        if(!sublist){
            fprintf(stderr, "Error: malloc returned NULL during resize\n");
            return NULL;
        }
        sublist->head = NULL;
        sublist->size = 0;
        new_buckets[x] = sublist;
    }
    // now new_buckets is a unique "buckets" to replace original.
   
    size_t old_capacity = map->capacity;
    map->capacity = new_capacity;

    for(size_t x = 0; x < old_capacity; ++x){
        if(map->buckets[x]->head == NULL) continue;
        MapNode *current_node = map->buckets[x]->head;

        while(current_node){
            size_t bucket_index = hm_hash_function(current_node->key, map);

            MapNode *next_node = current_node->next;

            current_node->next = new_buckets[bucket_index]->head;
            new_buckets[bucket_index]->head = current_node;

            current_node = next_node;
        }
        free(map->buckets[x]);

    }

    free(map->buckets);
    map->buckets = new_buckets;



    // for the original array, for all sub-buckets:
        // continue if array is empty
        // otherwise, for each node in array, calculate index and add to new list
    // Change capacity and map->buckets to new buckets.
    return true;
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
bool hm_contains_key(const char *key, HashMap *map){
    // Calculate index based on hash function
    if(!map){
        fprintf(stderr, "Error- invalid map passed to contains_key function.\n");
        return false;
    }
    size_t calculated_index = hm_hash_function(key, map);
    // Check valid index, or if that linked list is empty
    if(calculated_index >= map->capacity || map->buckets[calculated_index]->head == NULL) return false;

    MapNode *current_node = map->buckets[calculated_index]->head;

    while(current_node){
        if (current_node->key == key) return true;
        else current_node = current_node->next;
    }

    // Iterate through linked list, and return T/F
    return false;
}



/*
Function: contains_value
Purpose:  checks whether the current HashMap is storing the given integer
Params:   int value, HashMap pointer
Returns:  boolean
*/
bool hm_contains_value(int value, const HashMap *map){
    if(!map){
        fprintf(stderr, "Error- invalid map passed to contains_key function.\n");
        return false;
    }

    for(size_t x = 0; x < map->capacity; ++x){

        if (map->buckets[x]->head == NULL) continue;

        MapNode *current_node = map->buckets[x]->head;

        while(current_node){
            if(current_node->value == value)return true;
            current_node = current_node->next;
        }

    }
    // Iterate through linked list, and return T/F
    return false;
}


/*
Function: is_empty
Purpose: returns whether or not the map is empty, as a boolean.
Params:  HashMap pointer
Returns: boolean
*/
bool hm_is_empty(const HashMap *map){
    return (map->size == 0);
}


/*
Function: remove
Purpose: Given an integer, removes the value, if present, from the HashMap
Params:  int value, HashMap pointer
Returns: boolean
*/
bool hm_remove_key(char *key, HashMap *map){
    if(!map){
        fprintf(stderr, "Error- invalid map passed to remove_key function.\n");
        return false;
    }
    // Find insertion index using hash function
    size_t removal_index = hm_hash_function(key, map);
    // Check linked list at specified index
    if(removal_index >=map->capacity || map->buckets[removal_index]->head == NULL) return false;
    // If head is not null, iterate until found (TRACK PREVIOUS AND CURRENT NODE)
    MapNode *removal_node = map->buckets[removal_index]->head;
    MapNode *previous_node = map->buckets[removal_index]->head;
    
    while(removal_node->next != NULL){
        if (removal_node->key == key) break;
        removal_node = removal_node->next;
        previous_node = removal_node;
    }
    // If we exit the loop, but the current node is NOT the node to remove.
    if(removal_node->key != key) return false;

    // if node to remove is the linked list's head
    if(map->buckets[removal_index]->head == removal_node)
    {
        map->buckets[removal_index]->head = removal_node->next;
        free(removal_node);
        map->size--;
        return true;
    }
    previous_node->next = removal_node->next;
    free(removal_node);
    map->size--;
    return true;
}

/*
Function: delete_map
Purpose:  HashMap deletion; deletes all key/value pairs, then the internal pointer "array", then the struct in memory.
Params:   HashMap pointer
Returns:  boolean
*/
bool hm_delete_map(HashMap *map){
    if(!map){
        fprintf(stderr, "Error- invalid hash map passed to delete_map.\n");
        return false;
    }
    hm_clear_map(map);

    for(size_t x = 0; x < map->capacity; ++x){
        free(map->buckets[x]);
    }
    free(map->buckets);
    free(map);
    return true;
}