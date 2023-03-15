#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int v[5];

    for (int *ip = v; ip < &v[5]; ++ip) {
        *ip = ip - v;
    }

    for (int *ip = v; ip < &v[5]; ++ip) {
        printf("%i ", *ip);
    }
    putchar('\n');
    
    return EXIT_SUCCESS;
}
