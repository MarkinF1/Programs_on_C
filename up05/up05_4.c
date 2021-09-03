#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int
main (int argc, char *argv[]) 
{
    int fd = open(argv[1], O_RDONLY);
    ssize_t count = 1;
    unsigned short num = 1, min;
    unsigned char buf[2];
    while (num % 2 && count > 0) {
        count = read(fd, buf, 2);
        num = buf[0];
        num <<= 8;
        num += buf[1];
    }
    if (count <= 0) {
        return 0 ;
    }
    min = num;    
    while (count > 0) {
        count = read(fd, buf, 2);
        num = buf[0];
        num <<= 8;
        num += buf[1];
        if (!(num % 2)) {
            min = (min > num ? num : min);
        }
    }
    printf("%d\n", min);
}
