#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

volatile int par_pid, chek;

void
func(int sig) 
{
    signal(SIGUSR1, func);
    chek = 0;
}

int
main(int argc, char *argv[])
{
    int lel = atoi(argv[1]), fd[2], count = 1;
    unsigned int pid1, pid2;
    if (lel <= 1) {
        printf("Done\n");
        exit(0);
    }
    pipe(fd);
    signal(SIGUSR1, func);
    FILE *fd0 = fdopen(fd[0], "r");
    setbuf(stdin, NULL);
    if ((pid1 = fork())) {
        if ((pid2 = fork())) {
            fclose(fd0);
            dprintf(fd[1], "%d ", pid2);
            fflush(stdout);
            close(fd[0]);
            close(fd[1]);
            kill(pid1 + pid2 - wait(NULL), SIGKILL);
            printf("Done\n");
            fflush(stdout);
            return 0;
        } else {
            chek = 1;
            while (chek) {
                pause();     
            }      
            while (fscanf(fd0, "%d", &count) > 0) {
                chek = 1;
                printf("2 %d\n", count);
                fflush(stdout);
                if (++count == lel) {
                    fclose(fd0);
                    close(fd[0]);
                    close(fd[1]);
                    exit(0);
                } else {
                    dprintf(fd[1], "%d\n", count);
                    fflush(stdout);
                    kill(pid1, SIGUSR1);
                    while (chek) {
                        pause();
                    }
                }
            }
        }
    } else {
        fscanf(fd0, "%d", &pid1);
        printf("1 %d\n", count++);
        fflush(stdout);
        if (count == lel) {
            exit(0);
        }
        dprintf(fd[1], "%d\n", count);
        fflush(stdout);
        kill(pid1, SIGUSR1);
        pause();
        while (fscanf(fd0, "%d", &count) > 0) {
            chek = 1;
            printf("1 %d\n", count);
            fflush(stdout); 
            if (++count == lel) {
                fclose(fd0);
                close(fd[0]);
                close(fd[1]);
                exit(0);
            } else {
                dprintf(fd[1], "%d\n", count);
                fflush(stdout);
                kill(pid1, SIGUSR1);
                while (chek) {
                    pause();
                }
            }
        }
    }  
}
