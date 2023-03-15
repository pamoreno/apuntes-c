#include <stdlib.h>

double meand(double *v, size_t length)
{
    double mean = 0;

    for (size_t i = 0; i < length; ++i) {
        mean += v[i];
    }

    return mean / length;
}
