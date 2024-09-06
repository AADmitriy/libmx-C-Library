#include "libmx.h"


int mx_memcmp(const void *s1, const void *s2, size_t n) {
    unsigned char *byte_s1 = (unsigned char *)s1;
    unsigned char *byte_s2 = (unsigned char *)s2;

    while (*byte_s1 == *byte_s2 && n > 1) {
        byte_s1++;
        byte_s2++;
        n--;
    }

    return *byte_s1 - *byte_s2;
}


