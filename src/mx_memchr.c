#include "libmx.h"


void *mx_memchr(const void *s, int c, size_t n) {
    unsigned char *byte_s = (unsigned char *)s;

    while (n > 0) {
        if (*byte_s == c) {
            return (void *)byte_s;
        }
        n--;
        byte_s++;
    }
    return NULL;
}



