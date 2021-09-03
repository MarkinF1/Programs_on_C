#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

struct Msgbuf 
{
    long type;
    long long num1;
    long long num2;
};

int
main(int argc, char *argv[])
{
    struct Msgbuf buf;
    long long maxval = atoll(argv[5]);
    int i, msg, pid, key = atoi(argv[1]), n = atoi(argv[2]);
    msg = msgget(key, IPC_CREAT | 0600);
    for (i = 0; i < n; i++) {
        if ((pid = fork()) == -1) {
            msgctl(msg, IPC_RMID, 0);
            while (wait(NULL) > 0) {
                usleep(100);
            }
            return 1;
        } else if (!pid) {
            while (msgrcv(msg, &buf, 2 * sizeof(long long), i + 1, 0) >= 0) {
                long long x = buf.num1 + buf.num2; 
                printf("%d %lld\n", i, x);
                fflush(stdout);
                if (x > maxval || x < -maxval) {
                    msgctl(msg, IPC_RMID, 0);
                    break;
                }
                buf.num1 = buf.num2;
                buf.num2 = x;
                buf.type = x % n + 1;
                msgsnd(msg, &buf, 2 * sizeof(long long), 0);
            }
            exit(0);
        }
    }
    buf.type = 1;
    buf.num1 = atoll(argv[3]);
    buf.num2 = atoll(argv[4]);    
    msgsnd(msg, &buf, 2 * sizeof(long long), 0);
    while (wait(NULL) > 0) {
        usleep(100);
    }
    return 0;
}
