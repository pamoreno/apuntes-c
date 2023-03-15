#include <string.h>

void mi_strcat(char target[], const char source[])
{
    size_t inicio = strlen(target);
    size_t i;

    for (i = 0; source[i] != '\0'; ++i) {
        target[inicio + i] = source[i];
    }
    target[inicio + i] = '\0';
}
