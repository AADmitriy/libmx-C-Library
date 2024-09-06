#include <stdlib.h>

#include "libmx.h"

void mx_pop_front(t_list **list) {
    if (list == NULL || *list == NULL) {
        return;
    }

    t_list *current_element = *list;
    *list = current_element->next;

    free(current_element);
}

