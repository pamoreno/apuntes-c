#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 256

void strip_newline(char *s)
{
    char *p = NULL;

    if (NULL != s) {
        p = strrchr(s, '\n');

        if (NULL != p) {
            *p = '\0';
        }
    }
}

double maximo(double *ptrs[], size_t l)
{
    double m;

    m = *ptrs[0];
    while (--l) {
        if (*ptrs[l] > m) {
            m = *ptrs[l];
        }
    }
    return m;
}

int main (void)
{
    char input[MAX_LENGTH];
    char *perr = NULL;
    double d1 = 1.1e11;
    double d2 = 2.1e21;
    double d3 = 3.1e31;
    double d4 = 4.1e41;
    double *p2double[] = {NULL, NULL, NULL, NULL};
    double aux;

    p2double[0] = &d1;
    p2double[1] = &d2;
    p2double[2] = &d3;
    p2double[3] = &d4;

    for (size_t i = 0; i < sizeof(p2double) / sizeof(p2double[0]); ++i) {
        printf("Restan ingresar %li números\n", sizeof(p2double) / sizeof(p2double[0]) - i);
        printf("Por favor, ingrese un número: ");
        if (NULL == fgets(input, MAX_LENGTH, stdin)) {
            fprintf(stderr, "Error leyendo el %li-ésimo número\nNo hay posibilidad de reingresarlo.\n", i + 1);
            continue;
        }

        strip_newline(input);
        aux = strtod(input, &perr);
        if ('\0' != *perr) {
            fprintf(stderr, "\"%s\" no puede ser convertido a un número ¯\\_(ツ)_/¯\n", input);
            continue;
        }

        *p2double[i] = aux;
    }

    for (size_t i = 0; i < sizeof(p2double) / sizeof(p2double[0]); ++i) {
        printf("*p2double[%li] = %g\n", i, *p2double[i]);
    }

    aux = maximo(p2double, sizeof(p2double) / sizeof(p2double[0]));
    printf("y el máximo es: %g\n", aux);

    return EXIT_SUCCESS;
}
