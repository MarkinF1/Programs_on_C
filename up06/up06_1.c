#include <stdio.h>
#include <sys/stat.h>

int
main (int argc, char *argv[])
{
    long long sum = 0;
    for (int i = 1; i < argc; i++) {
        struct stat stb;
        if (lstat(argv[i], &stb) < 0) {
            continue;
        }
        if (!S_ISREG(stb.st_mode) || (S_ISLNK(stb.st_mode) && S_ISREG(stb.st_mode))) {
            continue;
        }
        if (stb.st_nlink > 1) {
            continue;
        }
        sum += stb.st_size;
    }
    printf("%lld\n", sum);
}
