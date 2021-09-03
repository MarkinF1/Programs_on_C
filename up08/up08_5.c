#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int
main(int argc, char *argv[])
{
    int n;
    pid_t pid1;
    setbuf(stdin, NULL);
    pid1 = fork();
    if (pid1) {
        wait(&pid1);
        if (!WIFEXITED(pid1)) {
            printf("-1");
        }
        return 0;
    }
    while (scanf("%d", &n) > 0) {
        pid1 = fork();
        if (pid1 == -1) {
            abort();
        }
        if (!pid1) {
            continue;
        }
        wait(&pid1);
        if (!WIFEXITED(pid1)) {
            abort();
        }
        printf("%d\n", n);
        fflush(stdout);
        exit(0);
    }
    exit(0);
}
