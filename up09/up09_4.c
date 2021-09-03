#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int
main(int argc, char *argv[])
{
    int i, fd = creat("apb.py", 0755);
    dprintf(fd, "#!/usr/bin/python\nprint(");
    for (i = 1; i < argc - 1; i++) {
        dprintf(fd, "%s*", argv[i]);
    }
    dprintf(fd, "%s)\nimport os\nos.remove(\"apb.py\")\n", argv[i]);
    close(fd);
    execlp("./apb.py", "./apb.py", NULL);
    exit(1);
}
