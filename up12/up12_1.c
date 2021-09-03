#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/wait.h>

/*
int semget(key_t key, int nsems, int semflg); созание массива nsems семафоров по ключу key, если 0, то не создаст новый а свяжет со старым
IPC_CREAT - creat massive, IPC_EXCL - и установл предыд будет ошибка если уже есть семаф
//----
int semctl(int semid, int semnum, int cmd, unsigned short *arg); 
GETALL - закидывает все значения семафоров в arg
IPC_RMID - удаляет массив
GETVAL - возвращ значение сем с номером semnum
SETALL
SETVAL
unsuccess - exit(-1)
//----
операции с массивом семафоров
int semop(int semid, struct sembuf *sops, unsigned nsops);
*/

int 
main(int argc, char *argv[])
{
    int n = atoi(argv[1]), key = atoi(argv[2]), max = atoi(argv[3]), shm, *mass, sem, i;
    key = ftok("/home/MarF1/ejudge/superfile", 'c');
    shm = shmget(key, 2 * sizeof(int), IPC_CREAT | 0600);
    mass = shmat(shm, 0, 0);
    sem = semget(key, n, IPC_CREAT | 0600);
    semctl(sem, 0, SETALL, 0);
    mass[0] = 0;
    mass[1] = 0;
    for (i = 1; i <= n; i++) {
        if (!fork()) {
            while (semop(sem, (struct sembuf[]) {{i - 1, -1, 0}}, 1) >= 0) {    
                printf("%d %d %d\n", i, mass[0]++, mass[1]);
                fflush(stdout);
                if (mass[0] > max) {
                    semctl(sem, 0, IPC_RMID);
                    shmctl(shm, IPC_RMID, NULL);
                    exit(0);
                }
                mass[1] = i;
                semop(sem, (struct sembuf[]) {{mass[0] % n * mass[0] % n 
                    * mass[0] % n * mass[0] % n, 1, 0}}, 1);
            }
            exit(0);
        }
    }
    semop(sem, (struct sembuf[]) {{0, 1, 0}}, 1);
    while (wait(NULL) > 0) {
        usleep(100);
    }
    return 0;
}
