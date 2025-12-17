#ifndef STTRUCTS_H
#define STTRUCTS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>       // Used in srand() for number generation
#include "./methods.h"


int *create_underlying_array(size_t);
DynArr create_DynArr(size_t);
void resize_array(size_t, DynArr *);  
bool array_is_empty(DynArr *);
int array_length(DynArr *);
int array_capacity(DynArr *);
void print_array(DynArr *);
void fill_array(size_t, DynArr *);
int find_minimum(DynArr *);
int find_maximum(DynArr *);
void da_append_value(int, DynArr *);
size_t find_value(int, DynArr *);
void remove_value(int, DynArr *);
void remove_at_index(size_t, DynArr *);
void add_at_index(int, size_t, DynArr *);
//----------------------------------------------
int quicksort_array(DynArr);
//----------------------------------------------
// int main(void)
// {
//     srand(time(NULL));
//     size_t starting_capacity = 4;
//     /* Initialize an empty dynamic array*/
//     DynArr example_array = create_DynArr(starting_capacity);
//     DynArr *arr_pointer = &example_array;
//     size_t amount = 10;
//     fill_array(amount, arr_pointer);
//     print_array(arr_pointer);
//     int xy_insert = 999; 
//     add_at_index(xy_insert, 0, arr_pointer);
//     print_array(arr_pointer);
//     return 0;
// }


/*
Function: create_underlying_array
Purpose: Creates a new allocation of memory, using calloc to clean, for DynArr object.
Params: capacity (length of array)
Returns: (int *) for newly created array.
 */
int *create_underlying_array(size_t capacity){
    /* If capacity is equal to 0 (size_t is unsigned), exit with error message. */
    if (capacity == 0){
        printf("Capacity is invalid.");
        exit(EXIT_FAILURE);
    }
    /* Calloc is used over malloc to clear memory, initially to set all parameters to 0.*/
    int *array = calloc(capacity, sizeof(int));
    if (array == NULL){
        printf("Malloc failure.");
        exit(EXIT_FAILURE);
    }
    return array;
}
/*
Function: create_DynArr
Purpose: Creates a new DynArr object, using create_underlying_array
Params: capacity (length of array)
Returns: DynArr object.
    - This is used to return the new object on the assignment operator within main().
 */
DynArr create_DynArr(size_t capacity){
    // if capacity == 0, set to 4, the lowest determined amount.
    if (capacity == 0){
        capacity = 4;
    }
    // Create an int pointer to the new underlying array, created from the called function.
    int *ptr = create_underlying_array(capacity);
    // This is then used to create an object of the DynArr class, with ptr as the items member.
    DynArr new_dyn_arr = {0, capacity, ptr};
    return new_dyn_arr;
}

/*
Function: resize_array
Purpose: Use realloc to create new block of memory, of size(capacity).
Params: capacity, DynArr pointer (to array to be edited)
Returns: N/A
 */
void resize_array(size_t capacity, DynArr *array){
    // If the capacity is invalid, smaller/eq to the current size, set to double the current capacity.
    if(array->size >= capacity){
        capacity = array->capacity * 2;
    }
    // Conditional to check if both the original capacity and new capacity are 0; if so, set to 4.
    // Created if resize_array() is called as a standalone function. 
    if (capacity == 0 && array->capacity == 0){
        capacity = 4;
    }
    /* Assign the realloc return pointer to a new type initially, in case realloc fails. */
    int *new_pointer = realloc(array->items, capacity * sizeof(int));
    if (new_pointer == NULL){
        printf("Reallocation Failed.");
        return;
    }
    else{
        /* If a NULL pointer was not returned, update the capacity/items pointer*/
        array->items = new_pointer;
        array->capacity = capacity;
        /* Iterate through each item, initializing new bytes to 0. */
        for (size_t i = array->size; i < capacity; ++i){
            array->items[i] = 0;
        }
    }
    return;
}
/*
Function: fill array
Purpose: Fills array with int values
Params: amount, DynArr pointer
Returns: N/A
 */
void fill_array(size_t amount, DynArr *array){
    // Iterate through the specified amount, generating pseudo-random numbers and appending to array.
    for (size_t x = 0; x < amount; ++x){
        // Create a random number
        int random_number = rand() % 255;
        // Set the current index in memory to the value of the iterator, and increment size.
        da_append_value(random_number, array);
    }
}
/*
Function: print_array
Purpose: Prints all elements within the array, based on array->size
Params:DynArr pointer
Returns: N/A
 */
void print_array(DynArr *array){
    for (size_t i = 0; i < array->size; ++i){
        if (i == 0){
            printf("[");
        }
        if (i == array->size -1){
            printf("%d]\n ", array->items[i]);
        }
        else {
            printf("%d, ", array->items[i]);
        }

    }
    
    printf("Size: %d, Capacity: %d\n", array_length(array), array_capacity(array));
}
/*
Function: find_minimum
Purpose: Returns (as an integer) the smallest integer within the array.
Params: DynArr pointer
Returns: integer
 */
int find_minimum(DynArr *array){
    int minimum = 0;

    for (size_t i = 0; i < array->size; ++i){
        if (i == 0) {
            minimum = array->items[i];
        }
        if (array->items[i] < minimum){
            minimum = array->items[i];
        }
    }
    return minimum;
}
/*
Function: find_maximum
Purpose: Returns (as an integer) the largest integer within the array.
Params: DynArr pointer
Returns: integer
 */
int find_maximum(DynArr *array){
    int maximum = 0;

    for (size_t i = 0; i < array->size; ++i){
        if (i == 0) {
            maximum = array->items[i];
        }
        if (array->items[i] > maximum){
            maximum = array->items[i];
        }
    }
    return maximum;
}
/*
Function: da_append_value
Purpose: Add a new integer to the end of the array, resizing if needed. 
Params: integer, DynArr pointer
Returns: N/A
 */
void da_append_value(int value, DynArr *array){
    // Initially checks if adding the new value would overflow specified array, and if so, resizes the array.
    if (array->size >= array->capacity){
        resize_array(array->capacity * 2, array);
    }
    // Set the next open value in memory to the parameter value, and increment size.
    array->items[array->size] = value;
    array->size += 1;
}
/*
Function: find_value
Purpose: Returns first instance of an integer within the array; returns NULL if value is not within array. 
Params: integer, DynArr pointer.
Returns: integer
 */
size_t find_value(int search_value, DynArr *array){
    for (size_t x = 0; x < array->size; ++x)
    {
        if (array->items[x] == search_value){
            // Return a pointer to the specific point in memory where the value was found.
            return x;
        }
    }
    // If value has not been found, return NULL
    return SIZE_MAX;
}

/*
Function: remove_value
Purpose: Returns first instance of an integer within the array; returns -1 if value is not within array. 
         Shifts all elements after removed element in array to the left, and resizes if needed. 
Params: integer, DynArr pointer.
Returns: integer
 */
void remove_value(int remove_value, DynArr *array){
    // First check if value is within array, and if so, return the index.
    size_t index_position = find_value(remove_value, array);
    // If the index position is larger than the size of the array, we can return immediately (no element)
    if(index_position == SIZE_MAX){
        return;
    }
    remove_at_index(index_position, array);
    // Otherwise, check if array will be resized.
    return;
}

/*Function: remove_at_index
Purpose: Given an index, remove this value and call helper function to shift all indices down
Params: size_t index, DynArr pointer.
Returns: N/A
 */
void remove_at_index(size_t index_position, DynArr *array){
    // If the position is greater than the number of elements, or greater than the current length of the list, immediately return.
    if(array->size <= index_position || array->capacity <= index_position) {
        return;
    }
    //starting at the element to be removed, take the next element and move it into the space to the left.
    for (size_t x = index_position; x < array->size - 1; ++x){
        array->items[x] = array->items[x + 1];
        // Implement moving elements down
    }
    // Decrement size of .size of the object
    array->size--;
    if (array->size != 0 && array->size <= array->capacity / 2){
        resize_array(array->capacity / 2, array);
    }
    return;

}
/*Function: is_empty
Purpose: Returns a boolean, dependent on whether or not the parameter array is empty.
Params: DynArr pointer.
Returns: Boolean
 */
bool array_is_empty(DynArr *array){
    if(array->size == 0) return true;
    else return false;
}

/*Functions: array_length, array_capacity
Purpose: Returns specific data members of a DynArr object.
Params: DynArr pointer.
Returns: integer
 */
int array_length(DynArr *array){
    return (int)array->size;
}
int array_capacity(DynArr *array){
    return (int)array->capacity;
}

/*Function: add_at_index
Purpose: Similar to add_at_index, but rather than removing at the given index, the value is removed, with all values shifted right,
        starting at the value already at that index.
Params: size_t index, DynArr pointer.
Returns: N/A
 */
void add_at_index(int value, size_t index_position, DynArr *array){
    // Check if index is greater than the current size; if so, appending would leave empty indices, so we return.
    if(index_position > array->size) return;

    // Check if array must be resized before insertion.
    if(array->size >= array->capacity){
        resize_array(array->capacity * 2, array);
    }
    // insert new value, and then shift all elements to the right.
    for(size_t i = array->size; i >= index_position; --i){
        if(i == index_position){
            array->items[i] = value;
            break;
        }
        else{
            array->items[i] = array->items[i-1];
        }
    }
    array->size++;
    return;
}
#endif