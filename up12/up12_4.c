#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/wait.h>

int
main(int argc, char *argv[])
{
    key_t key = ftok(argv[0], 'c');
    int i, sem, n = atoi(argv[1]);
    sem = semget(key, n, IPC_CREAT | 0600);
    semctl(sem, 0, SETALL, 0);
    setbuf(stdin, NULL);
    for (i = 0; i < n; i++) {
        if (!fork()) {
            break;
        }
    }
    if (i != n) {
        int num;
        while (semop(sem, (struct sembuf[]) {{i, -1, 0}}, 1) >= 0) {
            if (scanf("%d", &num) <= 0) {
                semctl(sem, 0, IPC_RMID);
                break;
            }
            printf("%d %d\n", i, num);
            fflush(stdout);
            semop(sem, (struct sembuf[]) {{(num % n + n) % n, 1, 0}}, 1);
        }
        exit(0);
    }
    semop(sem, (struct sembuf[]) {{0, 1, 0}}, 1);
    while (wait(NULL) > 0) {
        usleep(100);
    }
    return 0;
}
