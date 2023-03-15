#include <string.h>

int mi_strcmp(const char lhs[], const char rhs[])
{
    size_t i;

    for (i = 0; (lhs[i] == rhs[i]) && (rhs[i] != '\0'); ++i) ;

    return lhs[i] - rhs[i];
}
