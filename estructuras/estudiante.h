#pragma once

typedef struct estudiante {
    char *nombre;
    char *apellido;
} estudiante_t;


estudiante_t * estudiante_crear(const char  *nombre, const char *apellido);
void estudiante_free(estudiante_t **estudiante);
void estudiante_print_pretty(const estudiante_t *estudiante);
void estudiante_print_csv(const estudiante_t *estudiante);
int estudiante_comparar(const estudiante_t *lhs, const estudiante_t *rhs);
