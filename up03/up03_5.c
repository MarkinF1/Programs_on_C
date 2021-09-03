#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include <string.h>

enum { SIZE = 8, BEDA = 0xbedabeda, BAD = 0x0bad1dea };

//char *getline2(FILE *f);

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

int
main (int argc, char *argv[]) {
    char *str = NULL;
    int count_str = 0;
    while((str = getline2(stdin)) != NULL && *str != '\0'){
        long long num = 0;
        int count_num = 0, sum = 0;
        char *endptr = NULL, *str1, *check_str;
        str1 = str;
        count_str++;
        check_str = str + strlen(str) - 1;
        while(*str != '\n' && *str != '\0' && str != check_str){
            num = strtol(str, &endptr, 10);
            if (str == endptr) {
                break;
            }
            count_num++;
            if (!isspace(*endptr) && (*endptr < '0' || *endptr > '9') && *endptr != '\0') {
                sum = BEDA + count_str;
                break;
            }
            if (num >= INT_MAX) {
                num = count_num;
            } else if (num <= INT_MIN) {
                num = -count_num;
            }
            sum += num;
            str = endptr; 
        }
        if (!count_num) {
            sum = BAD + count_str;
        }
        printf("%d\n", sum);
        fflush(stdout);
        free(str1);
    }
}
