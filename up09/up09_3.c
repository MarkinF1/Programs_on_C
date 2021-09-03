#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int 
chek_func(int a)
{
    if (!(WIFEXITED(a) && !WEXITSTATUS(a))) {
        return 1;
    }
    return 0;
}    

int
main(int argc, char *argv[])
{
    int cmd1 = fork(), cmd2, cmd3;
    if (cmd1) {
        wait(&cmd1);
        if (chek_func(cmd1)) {
            if (!(cmd2 = fork())) {
                execlp("/bin/sh", "sh", "-c", argv[2], NULL);
                exit(1);
            }
            wait(&cmd2);
            if (chek_func(cmd2)) {
                return 1;
            }
        }
        if (!(cmd3 = fork())) {
            execlp("/bin/sh", "sh", "-c", argv[3], NULL);
            exit(1);
        }
        wait(&cmd3);
        if (chek_func(cmd3)) {
            return 1;
        }
        return 0;
    }
    execlp("/bin/sh", "sh", "-c", argv[1], NULL);
    exit(1);
}
