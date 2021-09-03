#include <stdio.h>
#include <stdlib.h>

void
normalize_path(char *buf)
{
    char *str1, *str2;
    str1 = buf;
    str2 = buf;
    while (*str2 != '\0') {
        if (*str2 != '/') {
            *str1 = *str2;
            str1++;
            str2++;
        } else {
            *str1 = *str2;
            str1++;
            str2++;
            while (*str2 == '/') {
                str2++;
            }
        }
    }
    *str1 = '\0';
}
