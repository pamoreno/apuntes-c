#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    double cube[2][2][2];

    printf("| `cube[%i][%i][%i]` | `%p`         |\n", 0, 0, 0, &cube[0][0][0]);
    printf("| `cube[%i][%i][%i]` | `%p`         |\n", 0, 0, 1, &cube[0][0][1]);
    puts("|                 |                          |");

    printf("| `cube[%i][%i][%i]` | `%p`         |\n", 0, 1, 0, &cube[0][1][0]);
    printf("| `cube[%i][%i][%i]` | `%p`         |\n", 0, 1, 1, &cube[0][1][1]);
    puts("|                 |                          |");

    printf("| `cube[%i][%i][%i]` | `%p`         |\n", 1, 0, 0, &cube[1][0][0]);
    printf("| `cube[%i][%i][%i]` | `%p`         |\n", 1, 0, 1, &cube[1][0][1]);
    puts("|                 |                          |");

    printf("| `cube[%i][%i][%i]` | `%p`         |\n", 1, 1, 0, &cube[1][1][0]);
    printf("| `cube[%i][%i][%i]` | `%p`         |\n", 1, 1, 1, &cube[1][1][1]);

    return EXIT_SUCCESS;
}
