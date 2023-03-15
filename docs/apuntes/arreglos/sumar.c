#include <stdlib.h>

void sumar(double lhs[], const double rhs1[], const double rhs2[], size_t n)
{
    for (size_t i = 0; i < n; ++i) {
        lhs[i] = rhs1[i] + rhs2[i];
    }
}
