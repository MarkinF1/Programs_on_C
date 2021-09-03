#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int
main(int argc, char *argv[])
{
    int pid;
    if (!(pid = fork())){
        int fd0, fd1, fd2;
        fd0 = open(argv[2], O_RDONLY);
        fd1 = open(argv[3], O_WRONLY | O_CREAT | O_APPEND, 0660);
        fd2 = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0660);
        if (fd0 == -1 || fd1 == -1 || fd2 == -1) {
            exit(42);
        }
        if (dup2(fd0, 0) == -1 || dup2(fd1, 1) == -1 || dup2(fd2, 2) == -1) {
            exit(42);
        }        
        close(fd0);
        close(fd1);
        close(fd2);
        execlp(argv[1], argv[1], NULL);
        exit(42);
    } else {
        wait(&pid);
        printf("%d", pid);
    }
    return 0;
}
