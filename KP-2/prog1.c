#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

unsigned n = 1;

void
func(int num)
{
    if (num * 2 + 1 >= n) {
        printf("%d\n", num);
        fflush(stdout);
        exit(0);
    } 
    if (!(fork())) {
        func(num * 2 + 1);
    }
    wait(NULL);
    printf("%d\n", num);
    fflush(stdout);
    if (!(fork())) {
        func(num * 2 + 2);
    }
    wait(NULL);
    exit(0);
}

int
main(int argc, char *argv[])
{
    int a = atoi(argv[1]) + 1;
    n = (n << a) - 1;
    func(0);
    return 0;
}
