#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int v[5];

    for (size_t i = 0; i < 5; ++i) {
        v[i] = i;
    }

    for (size_t i = 0; i < 5; ++i) {
        printf("%i ", v[i]);
    }
    putchar('\n');
    
    return EXIT_SUCCESS;
}
