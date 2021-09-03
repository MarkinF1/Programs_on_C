#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

struct Task
{
    unsigned uid;
    int gid_count;
    unsigned *gids;
};

int 
myaccess(const struct stat *stb, const struct Task *task, int access)
{
    int i, count = task->gid_count;
    gid_t gid1 = stb->st_gid;
    if (!task->uid) {
        return 1;
    }
    if (stb->st_uid == task->uid) {
        if (((stb->st_mode >> 6) & access) == access) {
            return 1;
        } else {
            return 0;
        }
    }
    for (i = 0; i < count; i++) {
        if (task->gids[i] == gid1) {
            if (((stb->st_mode >> 3) & access) == access) {
                return 1;
            } else {
                return 0;
            }
        }
    }
    if ((stb->st_mode & access) == access) {
        return 1;
    } 
    return 0;
}
