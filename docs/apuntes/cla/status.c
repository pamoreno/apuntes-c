#include "status.h"


static const char *err[] = {
    [ST_OK] = "ST_OK",
    [ST_ERR_NULL_PTR] = "ST_ERR_NULL_PTR",
    [ST_ERR_INSUFFICIENT_ARGUMENTS] = "ST_ERR_INSUFFICIENT_ARGUMENTS",
    [ST_ERR_TOO_MANY_ARGUMENTS] = "ST_ERR_TOO_MANY_ARGUMENTS",
    [ST_ERR_INVALID_NUMERATOR] = "ST_ERR_INVALID_NUMERATOR",
    [ST_ERR_INVALID_DENOMINATOR] = "ST_ERR_INVALID_DENOMINATOR",
    [ST_ERR_UNKNOWN_ARGUMENT] = "ST_ERR_UNKNOWN_ARGUMENT",
    [ST_ERR_LZERO_ARRAY] = "ST_ERR_LZERO_ARRAY",
    [ST_ERR_INVALID_ARG] = "ST_ERR_INVALID_ARG",
    [ST_ERR_UNKNOWN] = "ST_ERR_UNKNOWN",
};


const char *err_to_str(status_t st)
{
    if ((st >= 0) && (st <= ST_ERR_UNKNOWN)) {
        return err[st];
    }

    return "unknown";
}
