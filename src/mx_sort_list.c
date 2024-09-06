#include <stdlib.h>
#include <stdbool.h>

#include "libmx.h"

t_list *mx_sort_list(t_list *list, bool (*cmp)(void *a, void *b)) {
    if (list == NULL || cmp == NULL) {
        return NULL;
    }

    t_list *start = list;

    t_list *end;
    t_list *current_node;
    t_list *previous_node;
    t_list *next_node;

    for(end = NULL; end != start->next; end = current_node) {
        for (previous_node = current_node = start; current_node->next != end; previous_node = current_node, current_node = current_node->next) {
            next_node = current_node->next;

            if (cmp(current_node->data, next_node->data)) {
                current_node->next = next_node->next;
                next_node->next = current_node;

                if (current_node != start) {
                    previous_node->next = next_node;
                }
                else {
                    start = next_node;
                }

                t_list *temp = current_node;
                current_node = next_node;
                next_node = temp;
            }
        }
    }

    return start;
}



