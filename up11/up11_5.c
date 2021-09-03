#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <signal.h>

volatile int n = 0, count = 0;

void
func(int sig)
{
    if (sig == SIGINT && ++count < 4) {
        printf("%d\n", n);
        fflush(stdout);
        return;
    }
    if (count >= 4) {
        exit(0);
    }
    if (sig == SIGTERM) {
        exit(0);
    }
}

int
main(int argc, char *argv[])
{
    int qr, low, high, i, l;
    scanf("%d%d", &low, &high);
    signal(SIGTERM, func);
    signal(SIGINT, func);
    if (low == 1) {
        low++;
    }
    printf("%d\n", getpid());
    fflush(stdout);
    for (i = low; i < high; i++) {
        qr = (int) pow(i, 0.5);
        for (l = 2; l <= qr; l++) {
            if (!(i % l)) {
                break;
            }
        }
        if (l > qr) {
            n = i;
        }
    }
    printf("-1\n");
    fflush(stdout);
    return 0;
}
