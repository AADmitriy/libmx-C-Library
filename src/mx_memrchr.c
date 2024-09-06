#include "libmx.h"

void *mx_memrchr(const void *s, int c, size_t n) {
    unsigned char *byte_s = (unsigned char *)s;

    while (n > 0) {
        n--;
        if (*(byte_s + n) == c) {
            return (void *)(byte_s + n);
        }
        
    }
    return NULL;
}


