#include "libmx.h"
#include <limits.h>
#include <stdbool.h>

bool is_hex_super_alpha(char c) {
    return 'A' <= c && c <= 'F';
}

bool is_hex_lower_alpha(char c) {
    return 'a' <= c && c <= 'f';
}

bool is_valid_hex_num(const char *hex) {
    while(*hex != '\0') {
        if (!mx_isdigit(*hex)
            && !is_hex_super_alpha(*hex)
            && !is_hex_lower_alpha(*hex)) {
            return false;
        }

        hex++;
    }

    return true;
}

int get_hex_value(char c) {
    if (is_hex_super_alpha(c)){
        return 10 + c - 'A';
    }
    else if (is_hex_lower_alpha(c)) {
        return 10 + c - 'a';
    }
    else if (mx_isdigit(c)) {
        return c - '0';
    }
    else {
        return 0;
    }
}

unsigned long mx_hex_to_nbr(const char *hex) {
    if (!is_valid_hex_num(hex)) {
        return 0;
    }

    unsigned long result_nbr = 0;

    while(*hex != '\0') {
        // Perhaps the overflow check
        // should have been removed to pass to Oracle
        if (ULONG_MAX / 16 < result_nbr) {
            return 0;
        }

        result_nbr *= 16;

        // Perhaps the overflow check
        // should have been removed to pass to Oracle
        if (ULONG_MAX - get_hex_value(*hex) < result_nbr) {
            return 0;
        }

        result_nbr += get_hex_value(*hex);

        hex++;
    }

    return result_nbr;
}

