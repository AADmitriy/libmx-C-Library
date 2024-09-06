#include "libmx.h"

char *mx_itoa(int number) {
    if (number == 0) {return "0";}
    if (number == -2147483648) {return "-2147483648";}

    int remainder;
    char *str = NULL;
    bool negative = false;

    if (number < 0) {
        number *= -1;
        negative = true;
    }

    bool first = true;

    while (number != 0) {
        remainder = number % 10;
        number = (number - remainder) / 10;
        char num_char = '0' + remainder;
        char *new_str = mx_strjoin(&num_char, str);

        if (!first) {
            free(str);
        }
        else {
            first = false;
        }

        str = new_str;
    }

    if (negative) {
        char *new_str = mx_strjoin("-", str);
        free(str);
        str = new_str;
    }

    return str;
}


