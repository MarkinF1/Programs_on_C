#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <fcntl.h>
#include <unistd.h>

enum { BUF_SIZE = 30 };

int
main(int argc, char *argv[])
{
    long long n, i = 0, count = 0, min = LLONG_MAX;
    int fd = open(argv[1], O_RDWR);
    ssize_t chek, size = sizeof(long long);
    char buf[size];
    while ((chek = read(fd, buf, size)) > 0) {
        while (size - chek > 0) {
            chek += read(fd, buf + chek, size - chek);
        }
        n = *((long long *) buf);
        if (n < min) {
            min = n;
            count = i;
        }
        i++;
    }
    if (min != LLONG_MIN) { 
        min = -min;
    }
    if (i) {
        lseek(fd, count * (int) sizeof(long long), SEEK_SET);
        write(fd, &min, sizeof(min));
    }
    close(fd);
    return 0;
}
