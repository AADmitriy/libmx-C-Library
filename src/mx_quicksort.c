#include "libmx.h"


void swap(char **a, char **b) {
    char *temp = *a;
    *a = *b;
    *b = temp;
}


void quickSort(char **arr, int left, int right, int *count) {
    int i = left, j = right;
    char *pivot = arr[(left + right) / 2];
    int pivot_len = mx_strlen(pivot);

    while (i <= j) {
        while (mx_strlen(arr[i]) < pivot_len) { i++; }
        while (mx_strlen(arr[j]) > pivot_len) { j--; }

        if (i <= j) {
            if (i != j && mx_strlen(arr[i]) != mx_strlen(arr[j])) {
                *count += 1;
                swap(&arr[i], &arr[j]);
            }

            i++;
            j--;
        }
    }

    if (left < j) {
        quickSort(arr, left, j, count);
    }
    if (i < right) {
        quickSort(arr, i, right, count);
    }
}

int mx_quicksort(char **arr, int left, int right) {
    int count = 0;
    quickSort(arr, left, right, &count);
    
    return count;
}


