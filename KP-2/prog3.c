#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int
main(int argc, char *argv[])
{
    int pid1, pid2, fd1[2], fd2[2];
    pipe(fd1);
    pipe(fd2);
    if (!(pid1 = fork())) {
        if (!(pid2 = fork())) {
            close(fd1[1]);
            close(fd2[0]);
            double sum = 0, n;
            FILE *f = fdopen(fd1[0], "r");
            while (fscanf(f, "%lf", &n) > 0) {
                sum += n;
            }
            close(fd1[0]);
            fclose(f);
            dprintf(fd2[1], "%lf\n", sum);
            close(fd2[1]);
            exit(0);
        } else {
            close(fd2[0]);
            close(fd2[1]);
            close(fd1[0]);
            FILE *f = fopen(argv[1], "r");
            double n;
            while (fscanf(f, "%lf", &n) > 0) {
                if (n > 0) {
                    dprintf(fd1[1], "%f\n", n);
                }
            }
            close(fd1[1]);
            fclose(f);
            exit(pid2);
        }
    } else {
        close(fd1[0]);
        close(fd1[1]);
        close(fd2[1]);
        wait(&pid1);
        waitpid(WEXITSTATUS(pid1), NULL, 0);
        FILE *f = fdopen(fd2[0], "r");
        double sum;
        fscanf(f, "%lf", &sum);
        printf("%.10g\n", sum);
        fclose(f);
        close(fd2[0]);
        return 0;
    }       
}
