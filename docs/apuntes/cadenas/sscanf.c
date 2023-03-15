#include <stdio.h>
#include <stdlib.h>

#define MSG_ERR_INPUT "¡No se ingresó ningún valor!"

static const size_t MAX_SIZE = 100;

int main(void)
{
    char input[MAX_SIZE];
    double value;

    if (NULL == fgets(input, MAX_SIZE, stdin)) {
        fprintf(stderr, "%s\n", MSG_ERR_INPUT);
        return EXIT_FAILURE;
    }

    if (1 == sscanf(input, "%lf", &value)) {
        printf("Ingresaste %f\n", value);
    }

    return EXIT_SUCCESS;
}
