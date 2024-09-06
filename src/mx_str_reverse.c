#include "libmx.h"

void swap(char *c1, char *c2) {
    char temp = *c1;
    *c1 = *c2;
    *c2 = temp;
}

void mx_str_reverse(char *s) {
    int len = mx_strlen(s);

    for (int i = 0; i < len / 2; i++) {
        swap(&s[i], &s[len - i - 1]);
    }
}

