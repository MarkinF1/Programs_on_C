#include <stdio.h>
#include <stdlib.h>

enum { SIZE = 8 };

char 
*getline2(FILE *f) 
{
    size_t str_size = SIZE, count = 0;
    int c;
    char *str1 = NULL, *str2;
    str1 = (char *) calloc(1, str_size * sizeof(*str1));
    if (str1 == NULL) {
        return NULL;
    }
    str2 = str1;
    while ((c = getc_unlocked(f)) != EOF) {
        if (count == str_size) {
            str_size *= 2;
            str1 = (char *) realloc(str2, str_size * sizeof(*str1));
            if (str1 == NULL) {
                free(str2);
                return NULL;
            }
            str2 = str1;
            str1 = str2 + count; 
        }
        count++;
        *str1 = (char) c;
        str1++;
        if (c == '\n') {
            break;
        }
    }
    if (!count) {
        free(str1);
        return NULL;
    }
    *str1 = '\0';
    return str2;
}
