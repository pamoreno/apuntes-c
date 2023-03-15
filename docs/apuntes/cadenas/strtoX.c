#include <stdio.h>
#include <stdlib.h>

#define MSG_ERR_INPUT "¡No se ingresó ningún valor!"
#define MSG_ERR_TYPES "Esperaba [dlu]valor :("

static const size_t MAX_SIZE = 100;

int main(void)
{
    char input[MAX_SIZE];
    double dvalue;
    long lvalue;
    unsigned long ulvalue;

    if (NULL == fgets(input, MAX_SIZE, stdin)) {
        fprintf(stderr, "%s\n", MSG_ERR_INPUT);
        return EXIT_FAILURE;
    }

    switch (input[0]) {
    case 'd':
        dvalue = strtod(input + 1, NULL);
        printf("Ingresaste %f (double)\n", dvalue);
        break;
    case 'l':
        lvalue = strtol(input + 1, NULL, 10);
        printf("Ingresaste %li (long)\n", lvalue);
        break;
    case 'u':
        ulvalue = strtoul(input + 1, NULL, 10);
        printf("Ingresaste %lu (unsigned long)\n", ulvalue);
        break;
    default:
        fprintf(stderr, "%s\n", MSG_ERR_TYPES);
        return EXIT_FAILURE;
    }       

    return EXIT_SUCCESS;
}
