#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>

enum { BUF_SIZE = 16 };

int
main(int argc, char *argv[])
{
    long double res;
    long long max_first, max_second;
    int fd, count = 0, sign = 0, money;
    ssize_t count_buf;
    char buf[BUF_SIZE];
    max_first = INT_MIN;
    max_first--;
    max_second = max_first;
    for (int i = 1; i < argc; i++) {
        fd = open(argv[i], O_RDONLY);
        if (fd != -1) {
            while ((count_buf = read(fd, buf, BUF_SIZE)) == BUF_SIZE) {
                read(fd, &money, sizeof(int));
                if (money > max_first) {
                    max_second = max_first;
                    max_first = money;
                    count++;
                } else if (money == max_first) {
                    continue;
                } else if (money > max_second) {
                    max_second = money;
                    count++;
                }
            }
            close(fd);
        }
    }
    if (count > 1) {
        if (max_second < 0) {
            max_second = -max_second; 
            sign++;
        }
        res = max_second / 100 + (max_second % 100) * 0.01;
        if (sign) {
            res = -res;
        }
        printf("%.2Lf\n", res);
    }
}
