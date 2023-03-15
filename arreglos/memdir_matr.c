#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    double m[2][4];

    printf("| `m[%i][%i]` | `%p`         |\n", 0, 0, &m[0][0]);
    printf("| `m[%i][%i]` | `%p`         |\n", 0, 1, &m[0][1]);
    printf("| `m[%i][%i]` | `%p`         |\n", 0, 2, &m[0][2]);
    printf("| `m[%i][%i]` | `%p`         |\n", 0, 3, &m[0][3]);
    printf("| `m[%i][%i]` | `%p`         |\n", 1, 0, &m[1][0]);
    printf("| `m[%i][%i]` | `%p`         |\n", 1, 1, &m[1][1]);
    printf("| `m[%i][%i]` | `%p`         |\n", 1, 2, &m[1][2]);
    printf("| `m[%i][%i]` | `%p`         |\n", 1, 3, &m[1][3]);

    return EXIT_SUCCESS;
}
