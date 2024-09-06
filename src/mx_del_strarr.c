#include <stdlib.h>
#include"libmx.h"


void mx_del_strarr(char ***arr) {
    if (arr == NULL || *arr == NULL) {
        return;
    }

    char **temp = *arr;

    for (int i = 0; temp[i] != NULL; i++) {
        mx_strdel(&temp[i]);
    }

    free(*arr);

    *arr = NULL;
}

