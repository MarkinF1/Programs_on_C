#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int
main(int argc, char *argv[])
{
    int i, *pid, l, fd[2], cmd = 3;
    dup2(0, cmd);
    pid = (int *) malloc(argc * sizeof(int));
    for (i = 1; i < argc; i++) {
        pipe(fd);
        if ((pid[i] = fork()) == -1) {
            break;
        } else if (!pid[i]) {
            dup2(cmd, 0);
            if (i < argc - 1) {
                dup2(fd[1], 1);
            }
            if (close(fd[0]) || close(cmd) || close(fd[1])) {
                abort();
            }
            execlp(argv[i], argv[i], NULL);
            exit(1);
        }
        close(fd[1]);
        dup2(fd[0], cmd);
        close(fd[0]);
    }
    if (pid[i] == -1 || close(cmd)) {
        for (l = 1; l < i; l++) {
            kill(pid[l], SIGKILL);
        }
        free(pid);
        return 1;
    }
    for (l = 1; l < i; l++) {
        wait(&pid[0]);
        if (!WIFEXITED(pid[0])) {
            for (l = 1; l < i; l++) {
                kill(pid[l], SIGKILL);
            }
            free(pid);
            return 1;
        }
    }
    free(pid);
    return 0;
}
