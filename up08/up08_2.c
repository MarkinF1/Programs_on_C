#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>

int 
main(int argc, char *argv[])
{
    pid_t pid1, pid2;
    if ((pid1 = fork()) == 0) {
        if ((pid2 = fork()) == 0) {
            printf("3 ");
            fflush(stdout);
            exit(0);
        } else {
            wait(&pid2);
            printf("2 ");
            fflush(stdout);
            exit(0);
        }
    } else {
        wait(&pid1);
        printf("1\n");
    }
}
