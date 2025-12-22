#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>       
#include "linked_list_header.h"


//-------------------------- To Implement --------------------------
// DynArr *to_array(LinkedList *);
//---------------------------

int main (void)
{
    srand(time(NULL));
    LinkedList *new_list = ll_create_list();
    printf("Size: %zu\n", ll_get_size(new_list));
    //print_list(list_pointer);
    int amount = (rand() % 6) + 1 ;
    ll_add_value(99, new_list);
    ll_add_value(100, new_list);
    ll_fill_list(amount, new_list);
    ll_print_list(new_list);
    printf("Size: %zu\n", ll_get_size(new_list));
    printf(" Value 99 in list: %s\n", ll_get_node_by_value(99, new_list)? "True": "False");
    int delete_it = ll_delete_value(99, new_list);
    printf("Size: %zu\n", ll_get_size(new_list));
    ll_print_list(new_list);
    printf("\nList empty: %s\n", ll_list_is_empty(new_list)? "true":"false");
    ll_clear_list(new_list);
    printf("\nList empty: %s\n", ll_list_is_empty(new_list)? "true":"false");
    return 0;
    
}
/*
Function: ll_create_list
Purpose: Creates a new list in memory.
Params: N/A
Returns: pointer to Linked_List struct (or NULL).
 */
LinkedList *ll_create_list(void){
    LinkedList *new_list = malloc(sizeof(LinkedList));
    if (!new_list){
        fprintf(stderr, "Error: malloc returned NULL during LL creation.");
        return NULL;
    }
    new_list->head = NULL;
    new_list->size = 0;
    return new_list;
}
/*
Function: ll_get_size
Purpose: Return node count for linked list.
Params: list pointer
Returns: size_t
 */
// Returns size variable of struct object.
size_t ll_get_size(LinkedList *list){
    return list->size;
}
/*
Function: ll_get_node_by_value
Purpose: Return pointer to first node with matching int value, if any.
Params: (int) value, list pointer.
Returns: Node pointer
 */
Node *ll_get_node_by_value(int search_value, LinkedList *list){
    // Check if list exists or is not empty
    if(!list || list->size == 0) return NULL;
    // Set head to a variable
    Node *current = list->head;
    // Checks if no nodes exist within the list.
    if (!current) return NULL;
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
/*
Function: ll_get_head
Purpose: Return node count for linked list.
Params: list pointer
Returns: Node pointer
*/
Node *ll_get_head(LinkedList *list){
    return list->head;
}

/*
Function: ll_add_value
Purpose: Appends element to linked list, after node is created.
Params: value, list pointer
Returns: boolean
*/
bool ll_add_value(int value, LinkedList *list){
    if(!list){
        return false;
    }
    // Create new node struct with the given value, pointing to current head.
    Node *new_node = malloc(sizeof(Node));
    new_node->next = list->head;
    new_node->value = value;
    list->head = new_node;
    list->size++;
    return true;
    
}

/*
Function: ll_print_list
Purpose: Prints contents of linked list.
Params: list pointer
Returns: N/A
*/

void ll_print_list(LinkedList *list){
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

/*
Function: ll_fill_list
Purpose: Depending on passed amount, append randomly generated numbers as nodes.
Params: amount, list pointer
Returns: N/A
*/
void ll_fill_list(int amount, LinkedList *list){
    if(!list || amount <= 0) return;
    for (int x = 0; x < amount; ++x){
        ll_add_value(rand() % 255, list);
    }
}

/*
Function: ll_delete_value
Purpose: Deletes first node with a given value, if one exists.
Params: value, list pointer
Returns: boolean
*/
bool ll_delete_value(int value, LinkedList *list){
    if(!list) return false;
    // Locate node with the value, if within list.
    Node *node_to_delete = ll_get_node_by_value(value, list);
    if (!node_to_delete){
        return false;
    }
    return ll_delete_node(node_to_delete, list);
}
/*
Function: ll_delete_node
Purpose: Deletes node given as a parameter, if valid.
Params: node pointer, list pointer
Returns: boolean
*/
bool ll_delete_node(Node *node_deleted,  LinkedList *list){

    if (!list || !node_deleted) return false;

    Node *next = node_deleted->next;
    // If the current head is the node to be deleted, list->head is the only reference to this node.
    if(list->head == node_deleted){
        list->head = node_deleted->next;
        free(node_deleted);
        list->size--;
        return true;
    }
    // Otherwise, iterate through list until node is reach (to get previous node)
    Node *iterator_node = list->head;
    for(int t = 0; t < list->size; ++ t)
    {
        if (iterator_node->next == node_deleted) {
            break;
        }
        // If end of array is reached without finding the node (in case there are two lists, for instance)
        // return false.
        else if (!iterator_node ->next) {
            return false;
        }
        iterator_node = iterator_node->next;
    }
    // Now iterator node is the previous node, to point to the next node and remove the param node.
    iterator_node->next = node_deleted->next;
    free(node_deleted);
    list->size--;
    return true;
}
/*
Function: ll_clear_list
Purpose: Clears linked list.
Params: list pointer
Returns: boolean
*/
bool ll_clear_list(LinkedList *list){
    if(!list) return false;
    // List already cleared.
    if (list->size == 0 && list->head == NULL){
        return true;
    }
    // Set variables to track nodes to free
    Node *current_node = list->head;
    Node *next_node = list->head;

    for(int x = 0; x < list->size; ++x){
        if(current_node == NULL){
            break;
        }
        // Track the next node, free the current node, then point to the next.
        next_node = current_node->next;
        free(current_node);
        current_node = next_node;
    }
    // Set size to 0, head to NULL pointer.
    list->size = 0;
    list->head = NULL;
    return true;
}

/*
Function: ll_list_is_empty
Purpose: Returns boolean if list is empty
Params: list pointer
Returns: boolean
*/
bool ll_list_is_empty(LinkedList *list){
    return (list->size == 0 && list->head == NULL);
}
/*
Function: ll_contains
Purpose: Returns boolean depending on if list contains given integer or not.
Params: int value, list pointer
Returns: boolean
*/
bool ll_contains(int search_value, LinkedList *list){
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
/*
Function: ll_index_of_value
Purpose: returns index, as size_t, to first node with parameter element (if within list)
Params: int value, list pointer
Returns: size_t                     <---------------- Must be changed
*/
size_t ll_index_of_value(int value, LinkedList *list){
    if(list->size == 0 && list->head == NULL){
        return SIZE_MAX;
    }
    Node *current_node = list->head;

    for (int x = 1; x < list->size + 1; ++x){
        if(!current_node){
            return SIZE_MAX;
        }
        else if(current_node->value == value){
            return x;
        }
        else{
            current_node = current_node->next;
        }
    }
    return SIZE_MAX;
}

