#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int 
main(int argc, char *argv[])
{
    int pid1, f[2];
    pipe(f);
    if (!(pid1 = fork())) {
        int cmd1, cmd2;
        dup2(f[1], 1);
        close(f[1]);
        close(f[0]);
        if (!(cmd1 = fork())) {
            int fd = open(argv[4], O_RDONLY, 0);
            dup2(fd, 0);
            close(fd);
            execlp(argv[1], argv[1], NULL);
            exit(1);
        }
        wait(&cmd1);
        if (!(WIFEXITED(cmd1) && !WEXITSTATUS(cmd1))) {
            exit(0);
        } 
        if (!(cmd2 = fork())) {
            execlp(argv[2], argv[2], NULL);
            exit(1);
        }
        wait(&cmd2);
        exit(1);
    }
    close(f[1]);
    int cmd3;
    if (!(cmd3 = fork())) {
        dup2(f[0], 0);
        close(f[0]);
        int fd = open(argv[5], O_WRONLY | O_CREAT | O_APPEND, 0666);
        dup2(fd, 1);
        close(fd);
        execlp(argv[3], argv[3], NULL);
        exit(1);
    }
    close(f[0]);
    wait(&pid1);
    wait(&cmd3);
    return 0;
}
