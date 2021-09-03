#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int
main (int argc, char *argv[])
{
    struct tm tt;
    FILE *fd; 
    fd = fopen(argv[1], "r");
    time_t cur_time1, cur_time2;
    char flag = 0;
    memset(&tt, 0, sizeof(tt));
    tt.tm_isdst = -1;
    while (fscanf(fd, "%d/%d/%d%d:%d:%d", &tt.tm_year, &tt.tm_mon, &tt.tm_mday, &tt.tm_hour, 
    &tt.tm_min, &tt.tm_sec) != EOF) {
        tt.tm_isdst = -1;
        tt.tm_year -= 1900;
        tt.tm_mon -= 1;
        cur_time1 = mktime(&tt);
        if (flag != 0) {
            printf("%ld\n", cur_time1 - cur_time2);
        } else {
            flag = 1;
        }
        cur_time2 = cur_time1;
    }
    fclose(fd);
    return 0;
}
    
