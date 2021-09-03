#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int
main(int argc, char *argv[])
{
    int cmd1, fd[2], cmd2, cmd3;
    pipe(fd);
    if (!(cmd1 = fork())) {
        int fd1 = open(argv[4], O_RDONLY);
        dup2(fd1, 0);
        close(fd1);
        close(fd[0]);
        dup2(fd[1], 1);
        close(fd[1]);
        execlp(argv[1], argv[1], NULL);
        exit(1);
    }
    wait(NULL);
    if (!(cmd2 = fork())) {
        close(fd[1]);
        int f = open(argv[5], O_WRONLY | O_CREAT | O_APPEND, 0640);
        dup2(f, 1);
        close(f);
        dup2(fd[0], 0);
        close(fd[0]);
        execlp(argv[2], argv[2], NULL);
        abort();
    }
    wait(&cmd2);
    if (WIFEXITED(cmd2) && !WEXITSTATUS(cmd2)) {
        return 0;
    } else {
        if (!(cmd3 = fork())) {
            close(fd[1]);
            dup2(fd[0], 0);
            close(fd[0]);
            int f = open(argv[5], O_WRONLY | O_CREAT | O_APPEND, 0640);
            dup2(f, 1);
            close(f);
            execlp(argv[3], argv[3], NULL);
            exit(1);
        }
    }
    return 0;
}

