#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int
main(int argc, char *argv[])
{
    int n, i = 0, pidchek = 0;
    scanf("%d", &n);
    while (!pidchek && ++i <= n) {
        if (i != 1) {
            printf(" %d", i);
        } else {
            printf("%d", i);
        }
        fflush(stdout);
        pidchek = fork();
    }
    wait(&pidchek);
    if (i == 1) {
        printf("\n");
    }
    exit(0);
}
