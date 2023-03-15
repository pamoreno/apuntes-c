#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int array[5];

    printf("array[%i] -> 0x%x\n", 0, &array[0]);
    printf("array[%i] -> 0x%x\n", 1, &array[1]);
    printf("array[%i] -> 0x%x\n", 2, &array[2]);
    printf("array[%i] -> 0x%x\n", 3, &array[3]);
    printf("array[%i] -> 0x%x\n", 4, &array[4]);

    return EXIT_SUCCESS;
}
