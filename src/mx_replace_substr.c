#include "libmx.h"

char *mx_replace_substr(const char *str, const char *sub, const char *replace) {
    if (str == NULL || sub == NULL  || mx_strcmp(sub, "") == 0 || replace == NULL) {
        return NULL;
    }

    if (mx_strcmp(sub, replace) == 0) {
        return mx_strdup(str);
    }

    int sub_len = mx_strlen(sub);
    int replace_len = mx_strlen(replace);
    char *old_str = mx_strdup(str);
    char *new_str;

    int sub_str_index = mx_get_substr_index(old_str, sub);

    while (sub_str_index > 0) {
        int new_str_len = mx_strlen(old_str) + (replace_len - sub_len);
        new_str = mx_strnew(new_str_len);
        mx_strncpy(new_str, old_str, sub_str_index);
        mx_strcat(new_str, replace);
        mx_strcat(new_str, (old_str + sub_str_index + sub_len));
        free(old_str);
        old_str = new_str;
        sub_str_index = mx_get_substr_index(old_str, sub);
    }

    return old_str;
}


