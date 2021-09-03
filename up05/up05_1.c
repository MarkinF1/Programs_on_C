#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <inttypes.h>

int
main (int argc, char *argv[])
{
    unsigned sign, n, w;
    uint64_t sqr_n = 1;
    scanf("%o%o", &n ,&w);
    sqr_n <<= n;
    printf("|");
    for (uint32_t i = 0; i < 3; i++) {
        for (uint32_t k = 1; k < w; k++) {
            printf(" ");
        }
        printf("0|");
    }
    printf("\n"); 
    for (uint64_t i = 1; i < sqr_n; i++) {
        uint64_t chek = i;
        uint32_t kol = 0;
        while (chek) {
            kol++;
            chek >>= 3;
        }
        printf("|");
        for (uint32_t k = 1; k <= w - kol; k++) {
            printf(" ");
        }
        printf("%llo|", i);
        chek = i;
        kol = 0;
        while (chek) {
            kol++;
            chek /= 10;
        }
        for (uint32_t k = 1; k <= w - kol; k++) {
            printf(" ");
        }
        printf("%lld|", i);
        chek = i;
        kol = 0;
        if (i == sqr_n / 2) {
            for (uint32_t k = 0; k < w - 1; k++) {
                printf(" ");
            }
            printf("0|\n");
        } else {
            if (i < sqr_n / 2) {
                sign = 0;
            } else {
                sign = 1;
                chek = chek - sqr_n / 2;
            }
            while (chek) {
                kol++;
                chek /= 10;
            }
            for (uint32_t k = 1; k <= w - kol - sign; k++) {
                printf(" ");
            }
            if (sign) {
                chek = i - sqr_n / 2;
                printf("-");
            } else {
                chek = i;
            }
            printf("%lld|\n", chek);
        }
    }
} 
