#include"libmx.h"

char *mx_strstr(const char *s1, const char *s2) {
    if (*s2 == '\0') {
        return 0;
    }

    int len = mx_strlen(s2);
    char *str = mx_strchr(s1, s2[0]);

    while (str != 0) {
        int comparing = mx_strncmp(str, s2, len);

        if (comparing == 0) {
            return str;
        }

        str++;

        str = mx_strchr(str, s2[0]);
    }

    return 0;
}

