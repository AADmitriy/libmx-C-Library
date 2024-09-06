#include <stdlib.h>
#include "libmx.h"

int find_num_of_hex_digits(unsigned long nbr) {
    int num_digits = 1;

    nbr /= 16;

    while (nbr > 0) {
        nbr /= 16;
        num_digits++;
    }

    return num_digits;
}

char *mx_nbr_to_hex(unsigned long nbr) {
    int num_of_hex_digits = find_num_of_hex_digits(nbr);

    char *hex_str = mx_strnew(num_of_hex_digits);
    if (hex_str == NULL) {
        return 0;
    }

    for (int i = num_of_hex_digits - 1; i >= 0; i--) {
        int remainder = nbr % 16;

        if (remainder < 10) {
            hex_str[i] = remainder + '0';
        }
        else {
            hex_str[i] = remainder - 10 + 'a';
        }

        nbr /= 16;
    }

    return hex_str;
}

