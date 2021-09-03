#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int
main(int argc, char *argv[])
{
    int fd1[2], fd2[2];
    pipe(fd1);
    pipe(fd2);
    int pid1 = fork(), pid2, count = 1, num = atoi(argv[1]);
    if (pid1) {
        if (!(pid2 = fork())) {
            close(fd1[1]);
            close(fd2[0]);
            FILE *f1 = fdopen(fd1[0], "r");
            dprintf(fd2[1], "%d ", count);
            while(1) {
                fscanf(f1, "%d", &count); 
                if (count == num) {
                    break;
                }
                printf("2 %d\n", count);
                fflush(stdout);
                count++;
                dprintf(fd2[1], "%d ",  count);
            }
            fclose(f1);
            close(fd1[0]);
            close(fd2[1]);
            exit(0);
        } else {
            close(fd1[0]);
            close(fd1[1]);
            close(fd2[0]);
            close(fd2[1]);
            wait(&pid1);
            wait(&pid2);
            printf("Done\n");
            return 0;
        }
    } else {
        close(fd1[0]);
        close(fd2[1]);
        FILE *f2 = fdopen(fd2[0], "r");
        while(1) {
            fscanf(f2, "%d", &count);
            if (count == num) {
                break;
            }
            printf("1 %d\n", count);
            fflush(stdout);
            count++;
            dprintf(fd1[1], "%d ", count);
        }
        fclose(f2);
        close(fd1[1]);
        close(fd2[0]);
        exit(0);
    }
}
