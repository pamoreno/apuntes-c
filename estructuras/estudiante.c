#include "estudiante.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static char *mi_strdup(const char *s)
{
    char *copia;
    size_t l;

    if (NULL == s) {
        return NULL;
    }

    l = strlen(s);

    copia = (char *) malloc(l + 1);
    if (NULL == copia) {
        return NULL;
    }

    copia[l] = '\0';

    return copia;
}


estudiante_t * estudiante_crear(const char  *nombre, const char *apellido)
{
    estudiante_t *estudiante;

    if ((NULL == nombre) || (NULL == apellido)) {
        return NULL;
    }

    estudiante = (estudiante_t *) calloc(1, sizeof(estudiante_t));
    if (NULL == estudiante) {
        return NULL;
    }

    estudiante->nombre = mi_strdup(nombre);
    if (NULL == estudiante->nombre) {
        free(estudiante);
        return NULL;
    }

    estudiante->apellido = mi_strdup(apellido);
    if (NULL == estudiante->apellido) {
        free(estudiante->nombre);
        free(estudiante);
        return NULL;
    }

    return estudiante;
}


void estudiante_free(estudiante_t **estudiante)
{
    if (NULL != estudiante) {
        free((*estudiante)->nombre);
        (*estudiante)->nombre = NULL;
        free((*estudiante)->apellido);
        (*estudiante)->apellido = NULL;
        free(*estudiante);
        *estudiante = NULL;
    }
}


void estudiante_print_pretty(const estudiante_t *estudiante)
{
    if (NULL != estudiante) {
        printf("Nombre: %s\n", estudiante->nombre);
        printf("Apellido: %s\n", estudiante->apellido);
    }
}


void estudiante_print_csv(const estudiante_t *estudiante)
{
    if (NULL != estudiante) {
        printf("\"%s\",\"%s\"", estudiante->nombre, estudiante->apellido);
    }
}


int estudiante_comparar(const estudiante_t *lhs, const estudiante_t *rhs)
{
    int cmp_nombre;

    cmp_nombre = strcmp(lhs->nombre, rhs->nombre);

    return (0 != cmp_nombre) ? cmp_nombre : strcmp(lhs->apellido, rhs->apellido);
}
