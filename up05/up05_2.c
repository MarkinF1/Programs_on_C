#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const char str[] = {"rwxrwxrwx"};

int
main (int argc, char *argv[])
{
    for (int i = 1; i < argc; i++) {
        int num = atoi(argv[i]);
        int chek;
        for (int l = 2, count = 0; l >= 0; l--) {
            chek = num / (int) pow(10, l);
            chek %= 10;
            count = (2 - l) * 3;
            for (int k = 4; k > 0; k >>= 1) {
                if (chek >= k) {
                    printf("%c", str[count]);
                    chek -= k;
                } else {
                    printf("-");
                }
                count++;
            }
        }
    printf("\n");       
    }
}
