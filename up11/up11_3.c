#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <limits.h>

int
main(int argc, char *argv[])
{
    int count = 0, l, i, n, pid;
    char buf[PATH_MAX];
    n = atoi(argv[1]);
    for (i = 2; i < n + 2; i++) {
        if ((pid = fork()) == -1) {
            break;
        } else if (!pid) {
            FILE *fd = fopen(argv[i], "r");
            fscanf(fd, "%s", buf);
            execlp(buf, buf, NULL);
            abort();
        } 
    }
    for (l = 2; l < i; l++) {
        wait(&pid);
        if (WIFEXITED(pid) && !WEXITSTATUS(pid)) {
            count++;
        }
    }
    for (; l < argc; l++) {
        if (!fork()) {
            FILE *fd = fopen(argv[l], "r");
            fscanf(fd, "%s", buf);
            execlp(buf, buf, NULL);
            abort();
        }
        wait(&pid);
        if (WIFEXITED(pid) && !WEXITSTATUS(pid)) {
            count++;
        }
    }  
    printf("%d\n", count);
    return 0;             
}
