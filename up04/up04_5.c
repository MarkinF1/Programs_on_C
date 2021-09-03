#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

unsigned long long hash_function(unsigned long long);

int 
main (int argc, char *argv[])
{
    unsigned long long h;
    int fd;
    ssize_t count;
    char *filepath = argv[1];
    fd = open(filepath, O_CREAT | O_RDWR, 0660);
    h = strtoull(argv[2], NULL, 16);
    count = atoi(argv[3]);
    if (!count) {
        close(fd);
        return 0;
    }
    lseek(fd, (count - 1) * sizeof(h), SEEK_END);
    while (count) {
        write(fd, &h, sizeof(h));
        lseek(fd, -2 * (int)sizeof(h), SEEK_CUR);
        h = hash_function(h);
        count--;
    }
    close(fd);   
    return 0;
}
