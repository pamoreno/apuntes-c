#include "status.h"
#include "arg_parser.h"

#include <stdlib.h>

#define ARG_POS_NUMERATOR   1
#define ARG_POS_DENOMINATOR 2


status_t parse_arguments(int argc, char *argv[], double *num, double *den)
{
    char *pend = NULL;
    double _num;
    double _den;

    if (argc < 3) {
        return ST_ERR_INSUFFICIENT_ARGUMENTS;
    }

    if (argc > 3) {
        return ST_ERR_TOO_MANY_ARGUMENTS;
    }

    if ((NULL == argv) || (NULL == num) || (NULL == den)) {
        return ST_ERR_NULL_PTR;
    }

    _num = strtod(argv[ARG_POS_NUMERATOR], &pend);
    if ('\0' != *pend) {
        return ST_ERR_INVALID_NUMERATOR;
    }

    _den = strtod(argv[ARG_POS_DENOMINATOR], &pend);
    if ('\0' != *pend) {
        return ST_ERR_INVALID_DENOMINATOR;
    }

    *num = _num;
    *den = _den;

    return ST_OK;
}
