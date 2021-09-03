#include <stdio.h>
#include <string.h>

const char CONST_S[] = {"rwxrwxrwx"};

int
parse_rwx_permissions(const char *str) 
{
    if (!str) {
        return -1;
    }
    int first = 0, n = strlen(str);
    if (n != sizeof(CONST_S) - 1) {
        return -1;
    }
    for (int i = 0; i < n; i++) {
        first <<= 1;
        if (*str == CONST_S[i]) {
            first++;
        } else if (*str != '-') {   
            return -1;
        }
        str++;
    }
    return first;    
}
int main () {
    char s[11];
    scanf("%s", s);
    printf("%d", parse_rwx_permissions(s));
}
