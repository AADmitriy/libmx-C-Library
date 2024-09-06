#include "libmx.h"


void *mx_memmem(void *big, size_t big_len, void *little, size_t little_len) {
    if (big_len == 0 || big_len < little_len) {
		return NULL;
    }

    if (little_len == 0) {
        return big;
    }

    unsigned char *byte_little = (unsigned char *)little;
    unsigned char *str = (unsigned char *)mx_memchr(big, *byte_little, big_len);

    while (str != 0) {
        int comparing = mx_memcmp((void *)str, little, little_len);

        if (comparing == 0) {
            return (void *)str;
        }

        str++;

        str = (unsigned char *)mx_memchr((void *)str, *byte_little, big_len);
    }

    return NULL;
}



