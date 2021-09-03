#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int
main(int argc, char *argv[])
{
    int i, *pid[2];
    pid[0] = (int *) malloc((argc - 1) * sizeof(int));
    pid[1] = (int *) malloc((argc - 1) * sizeof(int));
    for (i = 0; i < argc - 1; i++) {
        if (!(pid[0][i] = fork())) {
            break;
        }
    }
    if (i < argc - 1 && !pid[0][i]) {
        int num = atoll(argv[i + 1]), sum = 0;
        while (num > 0) {
            sum += num & 1;
            num >>= 1;
        }
        exit(sum);
    }
    int pid1, status, l;
    for (i = 0; i < argc - 1; i++) {
        pid1 = wait(&status);
        l = 0;
        while (pid1 != pid[0][l]) {
            l++;
        }
        pid[1][l] = WEXITSTATUS(status);
    }
    for (i = 0; i < argc - 1; i++) {
        printf("%d\n", pid[1][i]);
    }
    free(pid[0]);
    free(pid[1]);
    return 0;
}
