#include <stdio.h>
#include <stdlib.h>

int
chek_function (unsigned num)
{
    long long count = 1;
    int del = 1;
    count <<= 24;
    for (int i = 0; i < 9; i++) {
        if (num < count) {
            if (!(num % del)) {
                return 1;
            } else {
                return 0;
            }
        }
        count <<=1;
        del <<=1;
    }
    return 0;
}

int
main (int argc, char *argv[])
{
    unsigned a;
    while (scanf("%u", &a) != EOF) {
        printf("%d ", chek_function(a));
    }
    printf("\n");
}
