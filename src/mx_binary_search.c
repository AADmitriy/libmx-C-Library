#include"libmx.h"

int mx_binary_search(char **arr, int size, const char *s, int *count) {
    int low = 0;
    int high = size - 1;

    while (low <= high) {
        int mid = (low + high) / 2;
        int cmp = mx_strcmp(arr[mid], s);

        *count += 1;

        if (cmp == 0) {
            return mid;
        }
        else if (cmp < 0) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }

    *count = 0;

    return -1;
}

