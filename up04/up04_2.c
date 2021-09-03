#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int 
main(int argc, char *argv[])
{
    unsigned short num;
    int fd = open(argv[1], 
        O_CREAT | O_WRONLY |
        O_TRUNC, S_IRUSR | S_IWUSR
    );
    char buf[2];
    while (scanf("%hu", &num) != EOF) {
        buf[1] = num;
        buf[0] = num >> 8;
        write(fd, buf, sizeof(num));
    }
    close(fd);
    return 0;
}
