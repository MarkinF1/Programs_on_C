#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


void
func(long long a) 
{
    int sum = 0;
    while (a != 0) {
        if (a % 4 < 0) {
            sum -= a % 4;
        } else {
            sum += a % 4;
        }
        a /= 4;
    }
    exit(sum);
}

int
main(int argc, char *argv[])
{
    long long num;
    int status, i, pid[argc];
    for (i = 1; i < argc; i++) {
        if (!(pid[i] = fork())) {
            num = atoll(argv[i]);
            func(num);
        }
    }
    for (i = 1; i < argc; i++) {
        waitpid(pid[i], &status, 0);
        printf("%d\n", WEXITSTATUS(status));
    }
    return 0;
}
