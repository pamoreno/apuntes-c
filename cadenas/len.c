#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char input[100] = "Hola Mundo!";
    size_t length;

    for (length = 0; input[length] != '\0'; ++length) ;

    printf("input tiene largo %lu\n", length);

    return EXIT_SUCCESS;
}
