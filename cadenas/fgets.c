#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char input[20];

    fgets(input, 20, stdin);
    printf("Ingresaste: >>%s<<\n", input);

    return EXIT_SUCCESS;
}
