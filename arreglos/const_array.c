#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    const int array[5];

    array[2] = array[0] + array[1];

    return EXIT_SUCCESS;
}
