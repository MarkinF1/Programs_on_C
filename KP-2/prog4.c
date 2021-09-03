#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <limits.h>

int 
main(int argc, char *argv[]) 
{
    int i, status;
    char *ch, str1[PATH_MAX], str2[PATH_MAX], *s1, *s2;
    s1 = str1;
    s2 = str2;
    for (i = argc - 1; i > 1; i--) {
        while (strcmp(argv[i], argv[1])) {
            sprintf(s1, "%s %s", argv[i], s2);
            ch = s1;
            s1 = s2;
            s2 = ch;
            i--;
        }
        if (!(fork())) {
            execlp("/bin/sh", "sh", "-c", s2, NULL);
            exit(1);
        }
        wait(&status);
        if (!WIFEXITED(status)) {
            return 1;
        }
        if (WEXITSTATUS(status)) {
            return 1;
        }
    }
}
