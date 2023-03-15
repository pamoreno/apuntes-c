#include <stdio.h>

void print_str_array_1 (char arr[][20], size_t n)
{
    for (size_t i = 0; i < n; ++i) {
        printf("%lu: >>>>%s<<<<\n", i, arr[i]);
    }
}

void print_str_array_2 (char *arr[], size_t n)
{
    for (size_t i = 0; i < n; ++i) {
        printf("%lu: >>>>%s<<<<\n", i, arr[i]);
    }
}
