#include <stdio.h>
#include <time.h>
#include <string.h>

enum { Y_CONST = 1925, M_CONST = 10, D_CONST = 7 };

int
main (int argc, char *argv[])
{
    int y, m, d;
    struct tm tt1;
    memset(&tt1, 0, sizeof(tt1));
    tt1.tm_isdst = -1;
    tt1.tm_year = Y_CONST - 1900;
    tt1.tm_mon = M_CONST - 1;
    tt1.tm_mday = D_CONST;
    long long t1;
    t1 = mktime(&tt1);
    while (scanf("%d%d%d", &y, &m, &d) > 0) {
        struct tm tt2;
        long long t2;
        memset(&tt2, 0, sizeof(tt2));
        tt2.tm_isdst = - 1;
        tt2.tm_year = y - 1900;
        tt2.tm_mon = m - 1;
        tt2.tm_mday = d;
        tt2.tm_hour = 12;
        t2 = mktime(&tt2);
        t2 -= t1;
        d = t2 / 3600 / 24;
        m = d / 30;
        y = m / 12;
        printf("%d %d %d\n", y+1, m % 12 + 1, d % 30 + 1);
    }
    return 0;
}
