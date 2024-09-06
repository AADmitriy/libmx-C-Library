#include "libmx.h"

void mx_print_strarr(char **arr, const char *delim) {
    if (arr == NULL || delim == NULL) return;


    while (*arr != NULL) {
        mx_printstr(*arr);
        arr++;

        if (*arr != NULL) {
            mx_printstr(delim);
        }
    }

    mx_printchar('\n');
}

