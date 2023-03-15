#include <stdlib.h>

void mi_strcpy(char target[], const char source[])
{
    for (size_t i = 0; source[i] != '\0'; ++i) {
        target[i] = source[i];
    }
}
