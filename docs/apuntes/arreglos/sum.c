#include <stdlib.h>

double sum(const double v[], size_t n)
{
    double suma = 0;

    for (size_t i = 0; i < n; ++i) {
        suma += v[i];
    }

    return suma;
}
