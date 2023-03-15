#include "status.h"
#include "meand.h"

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    double array[] = {34.2, 97.01, 0.0003, 1092.7, 5};
    double mean;
    
    puts("Prueba con valores típicos:");
    if (ST_OK != meand(&mean, array, 5)) {
        fprintf(stderr, "Ocurrió un error inesperado\n");
    } else {
        printf("\tMean: %.2f\n", mean);
    }
    
    puts("Prueba con arreglo de largo 0:");
    if (ST_OK != meand(&mean, array, 0)) {
        fprintf(stderr, "\tNo se pudo calcular la media (posiblemente el largo 0 tenga algo que ver)\n");
    } else {
        printf("\tMean: %.2f\n", mean);
    }
    
    puts("Prueba con arreglo NULL:");
    if (ST_OK != meand(&mean, NULL, 5)) {
        fprintf(stderr, "\tNo se pudo calcular la media (posiblemente el puntero nulo tenga algo que ver)\n");
    } else {
        printf("\tMean: %.2f\n", mean);
    }

    return EXIT_SUCCESS;
}
