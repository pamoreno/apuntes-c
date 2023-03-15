#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

int main(void)
{
    int array[SIZE] = {0};

    for (size_t i = 0; i <= SIZE; ++i) {
        array[i] = i;
    }

    for (size_t i = 0; i <= SIZE; ++i) {
        if (SIZE == i) {
            puts("---- limite ----");
        }
        printf("array[%lu] => %i\n", i, array[i]);
    }

    return EXIT_SUCCESS;
}
