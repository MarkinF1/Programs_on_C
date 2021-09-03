#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char *argv[])
{
    unsigned long long poz = 0;
    long long  neg = 0, a;
    for (int i = 1; i < argc; i++){
        a = atoi(argv[i]);
        if (a < 0)
            neg += a;
        else
            poz += a;
    }
    printf("%lld\n%lld\n", poz, neg);
}
