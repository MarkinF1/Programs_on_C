#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int
mysys(const char *str)
{
    int pid = fork(), status;
    if (!pid) {
        execlp("/bin/sh", "sh", "-c", str, NULL);
        _exit(127);
    } else if (pid == -1) {
        return -1;
    }
    waitpid(pid, &status, 0);
    if (WIFSIGNALED(status)) {
        return 128 + WTERMSIG(status);
    } else if (WIFEXITED(status)) {
        return WEXITSTATUS(status);
    }   
    return 1;   
}

