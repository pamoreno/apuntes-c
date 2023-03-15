#include <stdio.h>
#include <stdlib.h>

int main (void)
{
    char input[256];
    char *pend = NULL;
    double *data = NULL;
    double *aux = NULL;

    data = (double *) malloc(3 * sizeof(double));
    if (NULL == data) {
        fprintf(stderr, "Not enough memory\n");
        return EXIT_FAILURE;
    }
    
    for (size_t i = 0; i < 3; ++i) {
        printf("Ingrese un número: ");
        if (NULL == fgets(input, 256, stdin)) {
            fprintf(stderr, "Failed to read from stdin\n");
            free(data);
            return EXIT_FAILURE;
        }
        data[i] = strtod(input, &pend);
        if (('\0' != *pend) && ('\n' != *pend)) {
            fprintf(stderr, "Character %li ('%c') could not be converted as part of a double\n", pend - input, *pend);
            free(data);
            return EXIT_FAILURE;
        }
    }
    
    aux = realloc(data, 4 * sizeof(double));
    if (NULL == aux) {
        free(data);
        fprintf(stderr, "Falló realloc\n");
        return EXIT_FAILURE;
    }
    data = aux;

    printf("Ingrese un número: ");
    if (NULL == fgets(input, 256, stdin)) {
        fprintf(stderr, "Failed to read from stdin\n");
        free(data);
        return EXIT_FAILURE;
    }
    data[3] = strtod(input, &pend);
    if (('\0' != *pend) && ('\n' != *pend)) {
        fprintf(stderr, "Character %li ('%c') could not be converted as part of a double\n", pend - input, *pend);
        free(data);
        return EXIT_FAILURE;
    }

    printf("{%g", data[0]);
    for (size_t i = 1; i < 4; ++i) {
        printf(", %g", data[i]);
    }
    puts("}");

    return EXIT_SUCCESS;
}
