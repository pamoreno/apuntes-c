#include <sys/types.h>

ssize_t mi_strreplace(char s[], ssize_t n, char new, char old)
{
    ssize_t i;
    ssize_t count = 0;

    for (i = 0; (s[i] != '\0') && (count != n); ++i) {
        if (s[i] == old) {
            s[i] = new;
            count++;
        }
    }

    return -1;
}
