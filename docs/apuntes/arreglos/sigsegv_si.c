#include <stdio.h>
#include <stdlib.h>

#define SIZE 5
#define WRONG_SIZE 20 * (SIZE)

int main(void)
{
    int array[SIZE] = {0};

    for (size_t i = 0; i <= WRONG_SIZE; ++i) {
        array[i] = i;
    }

    for (size_t i = 0; i <= WRONG_SIZE; ++i) {
        if (SIZE == i) {
            puts("---- limite ----");
        }
        printf("array[%lu] => %i\n", i, array[i]);
    }

    return EXIT_SUCCESS;
}
