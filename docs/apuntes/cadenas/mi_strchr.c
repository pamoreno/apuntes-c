#include <sys/types.h>

ssize_t mi_strchr(const char s[], char c)
{
    ssize_t i;

    for (i = 0; s[i] != '\0'; ++i) {
        if (s[i] == c) {
            return i;
        }
    }

    return -1;
}
