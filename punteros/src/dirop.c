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
    printf("  La dirección de memoria de ip es: %p\n", (void *) &ip);
    printf("   La dirección de memoria de c es: %p\n", (void *) &c);
    printf("  La dirección de memoria de sz es: %p\n", (void *) &sz);
    
    return EXIT_SUCCESS;
}
