#include <stdio.h>
#include <stdlib.h>

int meand(double *mean, double *v, size_t l);

int main(void)
{
    double array[] = {34.2, 97.01, 0.0003, 1092.7, 5};
    double mean;
    
    puts("Prueba con valores típicos:");
    if (0 == meand(&mean, array, 5)) {
        printf("\tMean: %.2f\n", mean);
    } else {
        fprintf(stderr, "Ocurrió un error inesperado\n");
    }
    
    puts("Prueba con arreglo de largo 0:");
    if (0 == meand(&mean, array, 0)) {
        printf("\tMean: %.2f\n", mean);
    } else {
        fprintf(stderr, "\tNo se pudo calcular la media (posiblemente el largo 0 tenga algo que ver)\n");
    }
    
    puts("Prueba con arreglo NULL:");
    if (0 == meand(&mean, NULL, 5)) {
        printf("\tMean: %.2f\n", mean);
    } else {
        fprintf(stderr, "\tNo se pudo calcular la media (posiblemente el puntero nulo tenga algo que ver)\n");
    }

    return EXIT_SUCCESS;
}
