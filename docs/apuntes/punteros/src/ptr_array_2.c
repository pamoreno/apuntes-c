#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 256

double traza(float **m, size_t filas, size_t columnas);
void identar(int i);
void imprimir_matriz(float **m, size_t filas, size_t columnas, int ident);
void strip_newline(char *s);

int main (void)
{
    char input[MAX_LENGTH];
    char *perr = NULL;
    float fila0[] = {11, 12, 13, 14, 15};
    float fila1[] = {21, 22, 23, 24, 25};
    float fila2[] = {31, 32, 33, 34, 35};
    float fila3[] = {41, 42, 43, 44, 45};
    float fila4[] = {51, 52, 53, 54, 55};
    float *matriz[] = {fila0, fila1, fila2, fila3, fila4};
    float aux = 9e23;

    for (size_t i = 0; i < 5; ++i) {
        for (size_t j = 0; j < 5; ++j) {
            printf("Restan ingresar %li números\n", 25 - i*5 - j);
            printf("Por favor, ingrese un número: ");
            if (NULL == fgets(input, MAX_LENGTH, stdin)) {
                fprintf(stderr, "Error leyendo el (%li, %li)-ésimo elemento\nNo hay posibilidad de reingresarlo.\n", i + 1, j + 1);
                continue;
            }

            strip_newline(input);
            aux = strtod(input, &perr);
            if ('\0' != *perr) {
                fprintf(stderr, "\"%s\" no puede ser convertido a un número ¯\\_(ツ)_/¯\n", input);
                continue;
            }

            matriz[i][j] = aux;
        }
    }

    imprimir_matriz(matriz, 5, 5, 0);

    aux = traza(matriz, 5, 5);
    printf("y su traza es: %g\n", aux);

    return EXIT_SUCCESS;
}

double traza(float **m, size_t filas, size_t columnas)
{
    double t;

    if (filas == columnas) {
        for (size_t i = 0; i < filas; ++i) {
            t += m[i][i];
        }
    }

    return t;
}

void imprimir_matriz(float **m, size_t filas, size_t columnas, int ident)
{
    identar(ident);
    puts("{");
    for (size_t i = 0; i < filas; ++i) {
        identar(ident + 4);
        printf("{%6.3f", m[i][0]);
        for (size_t j = 1; j < columnas; ++j) {
            printf(", %6.3f", m[i][j]);
        }
        puts("},");
    }
    identar(ident);
    puts("}");
}

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

void identar(int i)
{
    while (i-- > 0) {
        putchar(' ');
    }
}
