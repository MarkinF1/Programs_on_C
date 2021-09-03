#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <limits.h>

enum { NUM = 10 };

int 
main(int argc, char *argv[])
{
    long long mass[10] = {};
    char path[PATH_MAX];
    scanf("%s", path);
    int i, count, fd = open(path, O_RDONLY, 0);
    struct stat stb;
    fstat(fd, &stb);
    if (S_ISREG(stb.st_mode)) {
        off_t file_size = stb.st_size;
        if (file_size) {
            void *index = mmap(NULL, file_size, PROT_READ, MAP_SHARED, fd, 0);
            if (index != MAP_FAILED) {
                unsigned char *index1 = index;
                for (i = 0; i < file_size; i++) {
                    if ((count = index1[i] - '0') < NUM && count >= 0) {
                        mass[count]++;
                    }
                }
            }
        }
    }
    for (i = 0; i < NUM; i++) {
        printf("%d %lld\n", i, mass[i]);
    }
    return 0;
}
