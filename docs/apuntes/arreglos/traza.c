#include <stdlib.h>

double matr_ones(double mat[][200], size_t n)
{
    double traza = 0;

    for (size_t i = 0; i < n; ++i) {
        traza += mat[i][i];
    }

    return traza;
}
