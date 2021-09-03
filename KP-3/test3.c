#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

FILE *f;

volatile int fd, chek = 1;

void
func1(void)
{
    long long sum = 0;
    int num, i;
    for (i = 0; i < 10; i++) {
        if (fscanf(f, "%d", &num) <= 0) {
            if (i == 0) {
                chek = 1;
		return;
            }
            break;
        }
	sum += num;
    }
    write(fd, &sum + sizeof(int), sizeof(int));
}

void
func2(void)
{
    FILE *fd1;
    long long sum = 1;
    int num, i;
    for (i = 0; i < 10; i++) {
        if (fscanf(f, "%d", &num) <= 0) {
            if (i == 0) {
                chek = 1;
		return;
            }
            break;
        }
	sum *= num;
    }
    fd1 = fdopen(fd, "r");
    fprintf(fd1, "%d\n", (int) sum);
}

int
main(int argc, char *argv[])
{
    f = fopen(argv[2], "r");
    int fd[2];
    pipe(fd);
    signal(SIGUSR1, func1);
    signal(SIGUSR2, func2());
    if (!fork()) {
        close(fd[1]);
	dup2(fd[0], 0);
	close(fd[0]);
	execlp(argv[1], argv[1], NULL);
	exit(1);
    }
    close(fd[0]);
    fd = fd[1];
    while (chek) {
        usleep(100);
    }
    return 0;
}
