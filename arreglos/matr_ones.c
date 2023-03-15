#include <stdlib.h>

void matr_ones(double mat[][200], size_t r, size_t c)
{
    if (c > 200) {
        return;
    }

    for (size_t i = 0; i < r; ++i) {
        for (size_t j = 0; j < c; ++j) {
            mat[i][j] = 1.;
        }
    }
}
