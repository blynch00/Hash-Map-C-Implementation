#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>       // Used in srand() for number generation
#include "./dyn_arr_header.h"


int main(void)
{
    srand(time(NULL));
    size_t starting_capacity = 4;

    /* Initialize an empty dynamic array*/

    DynArr *example_array = da_create_array(starting_capacity);
    if(example_array == NULL){ 
    fprintf(stderr, "Array could not be created.");
    return 1;
    }

    // Fill array with randomly generated values
    size_t amount = 8;

    if (!da_fill_array(amount, example_array)){
        fprintf(stderr, "Error filling array.\n");
        return 1;
    }
    da_print_array(example_array);
    printf("Min: %d, Max: %d\n", *da_find_minimum(example_array), *da_find_maximum(example_array));
    // Insert an element at a specified index.
    int xy_insert = 999; 
    if (!da_add_at_index(xy_insert, 2, example_array)){
        fprintf(stderr, "Error: array could not be added to dynamic array.");
        return 1;
    }
    da_print_array(example_array); 
    printf("Min: %d, Max: %d\n", *da_find_minimum(example_array), *da_find_maximum(example_array));
    // Print capacity before/after resize function is called
    printf("Capacity before resize: %zu\n", example_array->capacity);

    if (!da_resize_array(example_array->capacity *2, example_array)){
        fprintf(stderr, "Array could not be resized.");
        return 1;
    }
    printf("Capacity after resize: %zu\n", example_array->capacity);

    // find_index: first should be where the element was inserted, second should be SIZE_MAX.
    printf("Location of 999: %zu\n", da_find_value(999, example_array));
    printf("Location of 1000: %zu\n", da_find_value(1000, example_array));

    printf("Array deleted: %s\n", da_destroy_array(example_array)? "true":"false");

    return 0;
}

/*
Function: create_DynArr
Purpose: Creates a new DynArr object, using create_underlying_array
Params: capacity (length of array)
Returns: DynArr object.
    - This is used to return the new object on the assignment operator within main().
 */
DynArr *da_create_array(size_t capacity){
    // if capacity == 0, set to 4, the lowest determined amount.
    if (capacity <= 3){
        capacity = 4;
    }
    DynArr *new_array = malloc(sizeof(DynArr));
    if (new_array == NULL){
        fprintf(stderr, "Error: NULL pointer in creation of new array.\n");
        return NULL;
    }
    new_array->items = calloc(capacity, sizeof(int));
    if (new_array->items == NULL){
        fprintf(stderr, "Error: NULL pointer during creation of array->items.\n");
        free(new_array);
        return NULL;
    }
    new_array->size = 0;
    new_array->capacity = capacity;
    return new_array;
}



/*
Function: resize_array
Purpose: Use realloc to create new block of memory, of size(capacity).
Params: capacity, DynArr pointer (to array to be edited)
Returns: bool, dependent on outcome.
 */
bool da_resize_array(size_t capacity, DynArr *array){
    // If the capacity is invalid, smaller/eq to the current size, set to double the current capacity.
    if(array->size > capacity){
        capacity = array->size;
    }
    // Conditional to check if both the original capacity and new capacity are 0; if so, set to 4.
    // Created if resize_array() is called as a standalone function. 
    if (capacity == 0){
        capacity = 4;
    }
    /* Assign the realloc return pointer to a new type initially, in case realloc fails. */
    int *new_pointer = realloc(array->items, capacity * sizeof(int));
    if (new_pointer == NULL){
        fprintf(stderr, "Error: Realloc failed during resizing array.\n");
        return false;
    }
    /* If a NULL pointer was not returned, update the capacity/items pointer*/
    else{
        array->items = new_pointer;
        array->capacity = capacity;
        for (size_t i = array->size; i < capacity; ++i){
        array->items[i] = 0;
        }
        /* Iterate through each item, initializing new bytes to 0. */
        
    }
    return true;
}
/*
Function: da_append_value
Purpose: Add a new integer to the end of the array, resizing if needed. 
Params: integer, DynArr pointer
Returns: N/A
 */
bool da_append_value(int value, DynArr *array){
    // Initially checks if adding the new value would overflow specified array, and if so, resizes the array.
    if (array->size >= array->capacity){
        if(!da_resize_array(array->capacity * 2, array)){
            fprintf(stderr, "Error: Element failed to append. Resize array failed.\n");
            return false;
        }
    }
    // Set the next open value in memory to the parameter value, and increment size.
    array->items[array->size] = value;
    array->size ++;
    return true; 
}
/*
Function: fill array
Purpose: Fills array with int values
Params: amount, DynArr pointer
Returns: N/A
 */
bool da_fill_array(size_t amount, DynArr *array){
    if (!array || amount < 0){
        return false;
    }
    // Iterate through the specified amount, generating pseudo-random numbers and appending to array.
    for (size_t x = 0; x < amount; ++x){
        // Create a random number
        int random_number = rand() % 255;
        // Set the current index in memory to the value of the iterator, and increment size.
        if (!da_append_value(random_number, array)){
            fprintf(stderr, "Error: appending value during fill_array failed.\n");
        }
    }
    return true;
}
/*Functions: array_length, array_capacity
Purpose: Returns specific data members of a DynArr object.
Params: DynArr pointer.
Returns: integer
 */
size_t da_array_length(const DynArr *array){
    return array->size;
}
size_t da_array_capacity(const DynArr *array){
    return array->capacity;
}
/*
Function: print_array
Purpose: Prints all elements within the array, based on array->size
Params:DynArr pointer
Returns: N/A
 */
void da_print_array(const DynArr *array){
    if(!array) return;
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
    
    printf("Size: %zu, Capacity: %zu\n", da_array_length(array), da_array_capacity(array));
}
/*
Function: find_minimum
Purpose: Returns (as an integer) the smallest integer within the array. If array is empty, returns -1.
Params: DynArr pointer
Returns: integer
 */
int *da_find_minimum(DynArr *array){
    if (!array || array->size == 0) return NULL;
    int *minimum = &array->items[0];
    for (size_t i = 1; i < array->size; ++i){
        if (array->items[i] < *minimum){
            minimum = &array->items[i];
        }
    }
    return minimum;
}

/*
Function: find_maximum
Purpose: Returns (as an integer) the largest integer within the array; returns -1 otherwise.
Params: DynArr pointer
Returns: integer
 */
int *da_find_maximum(DynArr *array){
    if (!array || array->size == 0) return NULL;
    int *maximum = &array->items[0];
    for (size_t i = 1; i < array->size; ++i){
        if (array->items[i] > *maximum){
            maximum = &array->items[i];
        }
    }
    return maximum;
}


/*
Function: find_value
Purpose: Returns first instance of an integer within the array; returns SIZE_MAX if value is not within array. 
Params: integer, DynArr pointer.
Returns: integer
 */
size_t da_find_value(int search_value, DynArr *array){
    for (size_t x = 0; x < array->size; ++x)
    {
        if (array->items[x] == search_value){
            // Return a pointer to the specific point in memory where the value was found.
            return x;
        }
    }
    // If value has not been found, return SIZE_MAX; only becomes an issue when SIZE_MAX is considered a valid index.
    return SIZE_MAX;
}
/*Function: remove_at_index
Purpose: Given an index, remove this value and call helper function to shift all indices down
Params: size_t index, DynArr pointer.
Returns: N/A
 */
bool da_remove_at_index(size_t index_position, DynArr *array){
    // If the position is greater than the number of elements, or greater than the current length of the list, immediately return.
    if(array->size <= index_position) {
        return false;
    }
    //starting at the element to be removed, take the next element and move it into the space to the left.
    for (size_t x = index_position; x < array->size - 1; ++x){
        array->items[x] = array->items[x + 1];
        // Implement moving elements down
    }
    // Decrement size of .size of the object
    array->size--;
    if (array->size != 0 && array->size <= array->capacity / 4){
        if(!da_resize_array(array->capacity / 2, array)){
            fprintf(stderr, "Error: Array failed to resize during removal_at_index.\n");
            return false;
        }
    }
    return true;
}
/*
Function: remove_value
Purpose: Returns first instance of an integer within the array; returns -1 if value is not within array. 
         Shifts all elements after removed element in array to the left, and resizes if needed. 
Params: integer, DynArr pointer.
Returns: integer
 */
bool da_remove_value(int remove_value, DynArr *array){
    // First check if value is within array, and if so, return the index.
    size_t index_position = da_find_value(remove_value, array);
    // If the index position is larger than the size of the array, we can return false (not valid)
    if(index_position == SIZE_MAX){
        return false;
    }
    da_remove_at_index(index_position, array);
    // Otherwise, check if array will be resized.
    return true;
}

/*Function: is_empty
Purpose: Returns a boolean, dependent on whether or not the parameter array is empty.
Params: DynArr pointer.
Returns: Boolean
 */
bool da_array_is_empty(const DynArr *array){
    return(array->size == 0);
}



/*Function: add_at_index
Purpose: Similar to add_at_index, but rather than removing at the given index, the value is removed, with all values shifted right,
        starting at the value already at that index.
Params: size_t index, DynArr pointer.
Returns: N/A
 */
bool da_add_at_index(int value, size_t index_position, DynArr *array){
    // Check if index is greater than the current size; if so, appending would leave empty indices, so we return.
    if(index_position > array->size) return false;

    // Check if array must be resized before insertion.
    if(array->size >= array->capacity){
        if(!da_resize_array(array->capacity * 2, array)){
            fprintf(stderr, "Error: Resize failed during add_at_index- NULL pointer returned.\n");
            return false;
        }
        
    }
    // insert new value, and then shift all elements to the right.
    for(size_t i = array->size; i > index_position; --i){
        array->items[i] = array->items[i-1];
        }
    array->items[index_position] = value;
    array->size++;
    return true;
}

bool da_destroy_array(DynArr *array){
    if(!array){
        return false;
    }
    free(array->items);
    free(array);
    return true;

}