#include <stdio.h>
#include <stdlib.h>

double meand(double *, size_t);

int main(void)
{
    double array[5];
    
    printf("Mean: %.2f\n", meand(array, 0));

    return EXIT_SUCCESS;
}
