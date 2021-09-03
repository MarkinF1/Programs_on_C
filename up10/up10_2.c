#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int 
main(int argc, char *argv[]) 
{
    int n, fd[2], pid1, pid2;
    pipe(fd);
    if (!(pid1 = fork())) {
        pid2 = fork();
        if (pid2) {    
            close(fd[0]);
            close(fd[1]);
            wait(&pid2);
            exit(0);
        }
        long long sum = 0;
        close(fd[1]);
        while (read(fd[0], &n, sizeof(n)) > 0) {
            sum += n;
        }
        close(fd[0]);
        printf("%lld\n", sum);
        exit(0);
    }
    close(fd[0]);
    while (scanf("%d", &n) > 0) {
        write(fd[1], &n, sizeof(n));
    }
    close(fd[1]);
    wait(&pid1);
    return 0;
}
