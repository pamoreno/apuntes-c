#include <stdlib.h>

int meand(double *mean, double *v, size_t length)
{
    double _mean = 0;

    if ((NULL == mean) || (NULL == v)) {
        return -1;
    }

    if (0 == length) {
        return -2;
    }

    for (size_t i = 0; i < length; ++i) {
        _mean += v[i];
    }

    *mean = _mean / length;

    return 0;
}
