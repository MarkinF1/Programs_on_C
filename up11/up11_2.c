#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

volatile int flag = 0;

void
func(int sig)
{
    signal(SIGQUIT, func);
    signal(SIGINT, func);
    if (sig == SIGQUIT) {
        flag = 1;
    } else if (sig == SIGINT) {
        flag = 0;
    }    
}

int
main(int argc, char *argv[])
{
    signal(SIGQUIT, func);
    signal(SIGINT, func);
    printf("%d\n", getpid());
    fflush(stdout);
    unsigned int sum = 0, n;
    while (scanf("%d", &n) > 0) {
        if (flag) {
            sum *= n;
            printf("%d\n", sum);
            fflush(stdout);
        } else {
            sum += n;
            printf("%d\n", sum);
            fflush(stdout);
        }
    }
    return 0;            
}
