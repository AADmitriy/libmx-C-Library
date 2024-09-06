#include"libmx.h"

int mx_count_substr(const char *str, const char *sub) {
    int count = 0;
    str = mx_strstr(str, sub);

    while (str != 0) {
        count++;
        str++;
        str = mx_strstr(str, sub);
    }

    return count;
}

