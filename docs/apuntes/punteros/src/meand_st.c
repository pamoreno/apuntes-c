#include "meand.h"
#include "status.h"

#include <stdlib.h>

status_t meand(double *mean, double *v, size_t length)
{
    double _mean = 0;

    if ((NULL == mean) || (NULL == v)) {
        return ST_ERR_NULL_PTR;
    }

    if (0 == length) {
        return ST_ERR_LZERO_ARRAY;
    }

    for (size_t i = 0; i < length; ++i) {
        _mean += v[i];
    }

    *mean = _mean / length;

    return ST_OK;
}
