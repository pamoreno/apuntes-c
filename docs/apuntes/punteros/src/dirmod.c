#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char c = 'a';
    int ivar = 10;
    size_t sz = 1959;
    int *ip;

    ip = &ivar;

    printf("  El valor **almacenado** en ip es: %p\n", (void *) ip);
    printf("La dirección de memoria de ivar es: %p\n", (void *) &ivar);
    printf("    El valor almacenado en ivar es: %i\n", ivar);

    *ip = 303;

    printf("  El valor **almacenado** en ip es: %p\n", (void *) ip);
    printf("La dirección de memoria de ivar es: %p\n", (void *) &ivar);
    printf("    El valor almacenado en ivar es: %i\n", ivar);
    
    return EXIT_SUCCESS;
}
