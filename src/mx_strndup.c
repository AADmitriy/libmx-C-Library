#include <stdlib.h>

#include "libmx.h"

char *mx_strndup(const char *str, size_t n) {
    if (str == NULL) {
        return NULL;
    }

    char *new_str = mx_strnew(n);
    
    if (new_str == NULL) {
        return NULL;
    }

    mx_strncpy(new_str, str, n);

    return new_str;
}

