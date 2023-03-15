#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int v[5];

    for (int *ip = v; ip < &v[5]; ++ip) {
        printf("%p\n", ip);
    }
    
    return EXIT_SUCCESS;
}
