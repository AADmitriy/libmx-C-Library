#include "libmx.h"


void *mx_memmove(void *dst, void *src, size_t len) {
    unsigned char *byte_dst = (unsigned char *)dst;
    unsigned char *byte_src = (unsigned char *)src;

    char *temp = (char*)malloc(len);

    for (size_t i = 0; i < len; i++) {
        temp[i] = (char)byte_src[i];
    }

    for (size_t i = 0; i < len; i++) {
        byte_dst[i] = (unsigned char)temp[i];
    }

    mx_strdel(&temp);

    return dst;
}


