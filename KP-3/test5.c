#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int
main(int argc, char *argv[])
{
    int fd1[2], fd2[2], pid, cmd1, cmd2, cmd3, cmd4;
    pipe(fd1);
    cmd1 = fork();
    if (cmd1) {
        pid = fork();
        if (pid) {
            cmd4 = fork();
        }
    }
    if (!cmd1) {
        close(fd1[0]);
        dup2(fd1[1], 1);
        close(fd1[1]);
        execlp(argv[1], argv[1], NULL);
        exit(1);
    }
    close(fd1[1]);
    pipe(fd2);
    if (!pid) {
        dup2(fd1[0], 0);
        close(fd1[0]);
        dup2(fd2[1], 1);
        close(fd2[1]);
        if (!(cmd2 = fork())) {
            int f = open(argv[5], O_WRONLY | O_CREAT | O_TRUNC | 0600);
            dup2(f, 2);
            close(f);
            execlp(argv[2], argv[2], NULL);
            exit(1);
        }
        wait(&cmd2);
        if (WIFEXITED(cmd2) && !WEXITSTATUS(cmd2) && (!(cmd3 = fork()))) {
            execlp(argv[4], argv[4], NULL);
            exit(1);
        }
        exit(0);
    }
    close(fd2[1]);
    if (!cmd4) {
        dup2(fd2[0], 0);
        close(fd2[0]);
        execlp(argv[4], argv[4], NULL);
        exit(1);
    }
    while (wait(NULL) > 0) {
        usleep(100);
    }
    return 0;
}
