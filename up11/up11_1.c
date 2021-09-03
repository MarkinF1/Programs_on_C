#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

volatile int count = 0;

void
sig_func(int sig)
{
    if (count < 5) {
        printf("%d\n", count++);
        fflush(stdout);
    } else {
        exit(0);
    }
}

int
main(int argc, char *argv[])
{
    sigaction(SIGHUP, &(struct sigaction) { .sa_handler = sig_func, .sa_flags = SA_RESTART }, NULL);
    printf("%d\n", getpid());
    fflush(stdout);
    while (1) {
        pause();
    }
}
