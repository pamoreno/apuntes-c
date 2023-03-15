#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char c = 'a';
    int ivar = 10;
    size_t sz = 1959;
    int *ip;

    ip = &c;

    printf("  El valor **almacenado** en ip es: %p\n", (void *) ip);
    printf("La dirección de memoria de ivar es: %p\n", (void *) &ivar);
    printf("    El valor almacenado en ivar es: %i\n", ivar);
    printf("   La dirección de memoria de c es: %p\n", (void *) &c);
    printf("       El valor almacenado en c es: %c\n", c);

    *ip = 303;

    printf("  El valor **almacenado** en ip es: %p\n", (void *) ip);
    printf("La dirección de memoria de ivar es: %p\n", (void *) &ivar);
    printf("    El valor almacenado en ivar es: %i\n", ivar);
    printf("   La dirección de memoria de c es: %p\n", (void *) &c);
    printf("       El valor almacenado en c es: %c\n", c);
    
    return EXIT_SUCCESS;
}
