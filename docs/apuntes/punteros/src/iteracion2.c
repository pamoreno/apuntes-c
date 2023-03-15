#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int v[5];
    int *ip = v;

    for (size_t i = 0; i < 5; ++i) {
        ip[i] = i;
    }

    for (size_t i = 0; i < 5; ++i) {
        printf("%i ", ip[i]);
    }
    putchar('\n');
    
    return EXIT_SUCCESS;
}
