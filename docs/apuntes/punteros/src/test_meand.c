#include <stdio.h>
#include <stdlib.h>

double meand(double *, size_t);

int main(void)
{
    double array[] = {34.2, 97.01, 0.0003, 1092.7, 5};
    
    printf("Mean: %.2f\n", meand(array, 5));

    return EXIT_SUCCESS;
}
