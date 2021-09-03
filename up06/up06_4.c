#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

int 
main(int argc, char *argv[])
{
    struct dirent *dd;
    long long sum = 0;
    DIR *d;
    char path[PATH_MAX];
    if (!(d = opendir(argv[1]))) {
        exit(1);
    }
    while ((dd = readdir(d))) {
        if (!strcmp(dd->d_name, ".") || !strcmp(dd->d_name, "..")) {
            continue;
        } else {
            snprintf(path, sizeof(path), "%s/%s", argv[1], dd->d_name);
        }
        struct stat stb;
        if (stat(path,&stb) < 0) {
            continue;
        }
        if (!S_ISREG(stb.st_mode)) {
            continue;
        }
        if (stb.st_uid != getuid()) {
            continue;
        }
        if (!isupper(dd->d_name[0])) {
            continue;
        }
        sum += stb.st_size;
    }
    printf("%lld\n", sum);
    closedir(d);
}   
