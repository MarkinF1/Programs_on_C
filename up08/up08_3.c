#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

enum { MAX = 8 };

int 
main(int argc, char *argv[])
{
    pid_t pid1, pid2, pid3;
    int i = 1;
    if ((pid1 = fork()) > 0) {
        i++;
        if ((pid2 = fork()) > 0) {
            i++;
            if ((pid2 = fork()) > 0) {
                wait(&pid3);
                wait(&pid2);
                wait(&pid1);
                return 0;
            }
        }
    }
    char buf[MAX];
    read(0, buf, MAX);
    int num = atoi(buf);
    num *= num;
    printf("%d %d\n", i, num);
    fflush(stdout);
    exit(0); 
}
