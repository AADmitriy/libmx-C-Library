#include <stdbool.h>
#include <stdlib.h>
#include"libmx.h"


int count_length_without_extra_spaces(const char *str) {
    if (str == NULL) {
        return 0;
    }

    char *str_trimmed = mx_strtrim(str);
    char *ptr_to_str_trimmed= str_trimmed;
    int length = 0;

    while (*str_trimmed != '\0') {
        while (mx_isspace(*str_trimmed)) {
            str_trimmed++;
        }

        while (*str_trimmed != '\0' && !mx_isspace(*str_trimmed)) {
            length++;
            str_trimmed++;
        }

        if (*str_trimmed != '\0' && mx_isspace(*str_trimmed)) {
            length++;
        }
    }

    mx_strdel(&ptr_to_str_trimmed);

    return length;
}

char *mx_del_extra_whitespaces(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    int length = count_length_without_extra_spaces(str);

    char *result_str = mx_strnew(length);
    char *ptr_to_result_str = result_str;

    char *trimmed_str = mx_strtrim(str);
    char *ptr_to_trimmed_str = trimmed_str;

    if (result_str == NULL) {
        return NULL; // Memory allocation failed
    }

    while (*trimmed_str != '\0') {
        while (mx_isspace(*trimmed_str)) {
            trimmed_str++;
        }

        while (*trimmed_str != '\0' && !mx_isspace(*trimmed_str)) {
            *result_str++ = *trimmed_str++;
        }

        if (*trimmed_str != '\0' && mx_isspace(*trimmed_str)) {
            *result_str++ = ' ';
        }
    }

    mx_strdel(&ptr_to_trimmed_str);

    return ptr_to_result_str;
}

