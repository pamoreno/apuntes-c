#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int matr[2][3];

    for (size_t i = 0; i < 2; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            matr[i][j] = rand();
        }
    }

    printf("int matr[2][3] = {");
    for (size_t i = 0; i < 2; ++i) {
        printf("{%i", matr[i][0]);
        for (size_t j = 1; j < 3; ++j) {
            printf(", %i", matr[i][j]);
        }
        puts("},");
    }
    puts("};");

    return EXIT_SUCCESS;
}
