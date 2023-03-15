#include <stdio.h>
#include <stdlib.h>

#define SIZE 7

int main(void)
{
    char carray[SIZE];
    short sarray[SIZE];
    int iarray[SIZE];
    double darray[SIZE];

    printf("  sizeof char array: %lu bytes\n", sizeof(carray));
    printf(" sizeof short array: %lu bytes\n", sizeof(sarray));
    printf("   sizeof int array: %lu bytes\n", sizeof(iarray));
    printf("sizeof double array: %lu bytes\n", sizeof(darray));

    return EXIT_SUCCESS;
}
