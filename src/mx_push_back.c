#include <stdlib.h>
#include "libmx.h"

void mx_push_back(t_list **list, void *data) {
    if (list == NULL) {
        return;
    }

    t_list *new_node = mx_create_node(data);
    
    if (new_node == NULL) {
        return;
    }
    
    if (*list == NULL) {
        *list = new_node;
        return;
    }
    
    t_list *current_node = *list;
    
    while (current_node->next != NULL) {
        current_node = current_node->next;
    }
    
    current_node->next = new_node;
}

