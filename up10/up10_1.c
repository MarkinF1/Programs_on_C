#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <sys/wait.h>

int fd[2], fd1[2], fd2[2];

void 
close_func0(void) 
{
    close(fd[0]);
    close(fd1[0]);
    close(fd2[0]);
}

void
close_func1(void)
{
    close(fd[1]);
    close(fd1[1]);
    close(fd2[1]);
}

int
main(int argc, char *argv[]) 
{
    int pid1, pid2, pid3, status;
    pipe(fd);
    pipe(fd1);
    pipe(fd2);
    if (!(pid1 = fork())) {
        if (!(pid2 = fork())) {
            pid3 = fork();
        }
    }
    if (!pid3) {
        close_func0();
        time_t t = time(NULL);
        write(fd[1], &t, sizeof(t));
        write(fd1[1], &t, sizeof(t));
        write(fd2[1], &t, sizeof(t));
        close_func1();
        _exit(0);
    } 
    if (!pid2 && pid3) {
        close_func1();
        waitpid(pid3, &status, 0);
        time_t time;
        read(fd[0], &time, sizeof(time));
        close_func0();
        struct tm *tt;
        tt = localtime(&time);
        printf("D:%2d\n", tt->tm_mday);
        _exit(0);
    } 
    if (!pid1 && pid2 && !pid3) {
        close_func1();
        waitpid(pid2, &status, 0);
        time_t time;
        read(fd1[0], &time, sizeof(time));
        close_func0();
        struct tm *tt;
        tt = localtime(&time);
        printf("M:%2d\n", tt->tm_mon + 1);
        _exit(0);
    } else {
        close_func1();
        waitpid(pid1, &status, 0);
        time_t time;
        read(fd2[0], &time, sizeof(time));
        close_func0();
        struct tm *tt;
        tt = localtime(&time);
        printf("Y:%d\n", tt->tm_year + 1900);
    }
    return 0;  
}
