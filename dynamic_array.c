#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Struct for Dynamic Array; contains size, capacity, and pointer to array 
typedef struct{
        size_t size;
        size_t capacity;
        int *items;
    }DynArr;

int *create_underlying_array(size_t);
DynArr create_DynArr(size_t);
void resize_array(size_t);   // Must refactor + implement.
void fill_array(DynArr *);
void print_array(DynArr *);
int find_minimum(DynArr *);
int find_maximum(DynArr *);
//----------------------------------------------
int append_value(int, DynArr *);
int find_value(int, DynArr *);
int remove_value(int, DynArr *);
int remove_at_index(int, DynArr *);
int add_at_index(int, DynArr *);
bool is_empty(DynArr *);
int array_length(DynArr *);
int array_capacity(DynArr *);
int *resize_underlying_array(DynArr *, int);
//----------------------------------------------
int main(void)
{
    size_t starting_capacity = 0;
    /* Initialize an empty dynamic array*/
    DynArr example_array = create_DynArr(starting_capacity);
    DynArr *arr_pointer = &example_array;
    /* */
    fill_array(arr_pointer);
    print_array(arr_pointer);
    int min = find_minimum(arr_pointer);
    int max = find_maximum(arr_pointer);
    printf("Min: %d, Max: %d\n", min, max);
    return 0;
}

/* Function that creates the underlying data structure for dynamic array. */

int *create_underlying_array(size_t capacity){

    if (capacity <= 0){
        printf("Capacity is invalid.");
        exit(EXIT_FAILURE);
    }
    int *array = malloc(capacity * sizeof(int));
    if (!array){
        printf("Malloc failure.");
        exit(EXIT_FAILURE);
    }
    return array;
}

DynArr create_DynArr(size_t capacity){
    // See if capacity == 0, and if so, set it to 4, the lowest amount.
    if (capacity == 0){
        capacity = 4;
    }

    int *ptr = create_underlying_array(capacity);
    DynArr new_dyn_arr = {0, 4, ptr};
    if (!new_dyn_arr.items){
        printf("Failed to create underlying array.");
        exit(EXIT_FAILURE);
    }
    return new_dyn_arr;
}

void fill_array(DynArr *array){
    for (int x = 0; x < 10; ++x){
        if(array->capacity <= array->size)
        {
            if (array->capacity == 0){
                array->capacity = 4;
            }
            else array->capacity *= 2;
            array->items = realloc(array->items, array->capacity * sizeof(array->items));
        }
        array->items[array->size] = x;
        array->size += 1;
    }
}

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
    printf("\nCapacity: %d\n\n", array->capacity);
}

int find_minimum(DynArr *array){
    int minimum = -1;

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

int find_maximum(DynArr *array){
    int maximum = -1;

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