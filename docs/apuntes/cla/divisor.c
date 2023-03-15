#include "status.h"
#include "arg_parser.h"

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
    status_t st;
    double num;
    double den;

    st = parse_arguments(argc, argv, &num, &den);
    if (ST_OK != st) {
        fprintf(stderr, "Failed to parse arguments (%s)\n", err_to_str(st));
        return EXIT_FAILURE;
    }

    printf("%g\n", num / den);

    return EXIT_SUCCESS;
}
