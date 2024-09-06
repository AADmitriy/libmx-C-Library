#include <stdlib.h>

#include "libmx.h"

void mx_pop_back(t_list **list) {
    if (list == NULL || *list == NULL) {
        return;
    }

    t_list *current_node = *list;
    t_list *previous_node = current_node;

    while (current_node->next != NULL) {
        previous_node = current_node;
        current_node = current_node->next;
    }

    if (previous_node == current_node) {
        free(current_node);
        *list = NULL;
    }
    else {
        free(current_node);
        previous_node->next = NULL;
    }
}

