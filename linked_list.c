#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>       
#include "./methods.h"
#include "./dynamic_array.h"

LinkedList *create_list(void);
int get_size(LinkedList *);
struct Node *get_head(LinkedList *);
Node *get_node_by_value(int,LinkedList *);
int add_value(int, LinkedList *);
void fill_list(int, LinkedList *);
void print_list(LinkedList *);
int delete_value(int, LinkedList *);
int delete_node(Node *,  LinkedList *);
int clear_list(LinkedList *);
bool list_is_empty(LinkedList *);
bool contains(int, LinkedList *);
int index_of_value(int, LinkedList *);
//-------------------------- To Implement --------------------------
DynArr *to_array(LinkedList *);
//---------------------------

int main (void)
{
    srand(time(NULL));
    LinkedList *new_list = create_list();
    printf("Size: %d\n", get_size(new_list));
    //print_list(list_pointer);
    int amount = rand() % 6;
    
    add_value(99, new_list);
    add_value(100, new_list);
    fill_list(amount, new_list);
    print_list(new_list);
    printf("Size: %d\n", get_size(new_list));
    printf("%s\n", get_node_by_value(99, new_list)? "True": "False");
    int delete_it = delete_value(99, new_list);
    printf("Size: %d\n", get_size(new_list));
    print_list(new_list);
    return 0;
    
}

LinkedList *create_list(void){
    LinkedList *new_list = malloc(sizeof(LinkedList));
    if (!new_list){
        printf("New List could not be created.");
        return NULL;
    }
    else{
        new_list->head = NULL;
        new_list->size = 0;
        return new_list;
    }
}



// Returns size variable of struct object as integer.
int get_size(LinkedList *list){
    return (int)list->size;
}

// Given a value, traverse nodes until either all nodes are visited, or node is found and returned.
Node *get_node_by_value(int search_value, LinkedList *list){
    Node *current = list->head;
    if (!current){
        return NULL;
    }
    for (size_t x = 0; x < list->size; ++x){
        // if we reach an null node, or find a matching node, return current index 
        // (either a NULL node, or a pointer to the specific node).
        if (current == NULL || current->value == search_value){
            return current;
        }
        // Set current to the next variable.
        current = current->next;
    }
    // NULL pointer returned if not found.
    return NULL;
}

struct Node *get_head(LinkedList *list){
    return list->head;
}

int add_value(int value, LinkedList *list){
    // Create new node struct with the given value, pointing to current head.
    Node *new_node = malloc(sizeof(Node));
    new_node->next = list->head;
    new_node->value = value;
    list->head = new_node;
    list->size++;
    return 0;
    
}

// Print list dependent on the node count.
void print_list(LinkedList *list){
    if (list->size == 0){
        printf("[None]\n");
        return;
    } 
    // variable to point to current node, checking value and printing if applicable.
    Node *current_node = list->head;
    for(size_t x = 0; x < list->size; ++x){
        if (!current_node){
            printf("[None]");
            return;
        }
        else{
            // Print value and point to next value.
            printf("[%d] => ", current_node->value);
            current_node = current_node->next;
        }
    }
    printf("[None]\n");
}

void fill_list(int amount, LinkedList *list){
    for (int x = 0; x < amount; ++x){
        add_value(rand() % 255, list);
    }
}

int delete_value(int value, LinkedList *list){
    // Locate node with the value, if within list.
    Node *node_to_delete = get_node_by_value(value, list);
    if (!node_to_delete){
        return -1;
    }
    return delete_node(node_to_delete, list);
}

int delete_node(Node *node_deleted,  LinkedList *list){
    Node *next = node_deleted->next;

    if(list->head == node_deleted){
        list->head = node_deleted->next;
        free(node_deleted);
        list->size--;
        return 1;
    }

    Node *iterator_node = list->head;
    for(int t = 0; t < list->size; ++ t)
    {
        if (iterator_node->next == node_deleted) {
            break;
        }
        else if (!iterator_node ->next) {
            return 1;
        }
        iterator_node = iterator_node->next;
    }
    // Now iterator node is the previous node, to point to the next node and remove the param node.
    iterator_node->next = node_deleted->next;
    free(node_deleted);
    list->size--;
    return 1;
}

int clear_list(LinkedList *list){
    if (list->size == 0 && list->head == NULL){
        return 1;
    }
    Node *current_node = list->head;
    Node *next_node = list->head;
    for(int x = 0; x < list->size; ++x){
        if(current_node == NULL){
            break;
        }
        next_node = current_node->next;
        free(current_node);
        current_node = next_node;
    }
    list->size = 0;
    return 1;
}


bool list_is_empty(LinkedList *list){
    if (list->size == 0 && list->head == NULL){
        return true;
    }
    else{
        return false;
    }
}

bool contains(int search_value, LinkedList *list){
    if(list->size == 0 && list->head == NULL){
        return false;
    }
    Node *current_node = list->head;

    for (int x = 0; x < list->size; ++x){
        if(!current_node){
            return false;
        }
        else if(current_node->value == search_value){
            return true;
        }
        else{
            current_node = current_node->next;
        }
    }
    return false;
}

int index_of_value(int value, LinkedList *list){
    if(list->size == 0 && list->head == NULL){
        return -1;
    }
    Node *current_node = list->head;

    for (int x = 1; x < list->size + 1; ++x){
        if(!current_node){
            return -1;
        }
        else if(current_node->value == value){
            return x;
        }
        else{
            current_node = current_node->next;
        }
    }
    return -1;
}

// DynArr *to_array(LinkedList *list){
//     DynArr *new_array = malloc(list->size * sizeof(DynArr));
//     }
    
//     return new_array;
// }