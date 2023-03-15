#include <stdio.h>
#include <stdlib.h>

double meand(double *, size_t);

int main(void)
{
    double *array = NULL;
    
    printf("Mean: %.2f\n", meand(array, 5));

    return EXIT_SUCCESS;
}
