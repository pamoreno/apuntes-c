#include <stdlib.h>

void uniform(double v[], size_t n, double a, double b)
{
    for (size_t i = 0; i < n; ++i) {
        v[i] = (b - a) * (rand() / (double) RAND_MAX) + a;
    }
}
