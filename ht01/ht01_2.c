#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

int32_t
satsum (int32_t v1, int32_t v2)
{
    int32_t res, bol;
    uint32_t num = -1;
    bol = __builtin_sadd_overflow(v1, v2, &res);
    if (bol) {
        num >>= 1;
        if (v1 < 0) {
            num = ~num;
        }
        res = num;
    }
    return res;
}   
