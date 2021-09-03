#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

enum { BUF_SIZE = 16 };

int
main (int argc, char *argv[])
{
    unsigned long long num = 0, sum = 0;
    int sign = 0, chek = 0;
    ssize_t count_read;
    char buf[BUF_SIZE];
    while ((count_read = read(0, buf, BUF_SIZE)) > 0) {
        for (int i = 0; i < count_read; i++) {
            while (i < count_read && isspace(buf[i])) {
                i++;
                chek = 1;
            }
            if (chek) {
                sum += (sign == 0 ? num : -num);
                num = 0;
                sign = 0;
            }
            if (i < count_read && buf[i] == '-') {
                sign = 1;
                i++;
            }
            while (i < count_read && buf[i] >= '0' && buf[i] <= '9') {
                num = num * 10 + buf[i] - '0';
                i++;
            }
            chek = (i == count_read ? 0 : 1);
        }
    }
    sum += (sign == 0 ? num : -num);
    printf("%lld\n", sum);
}
            
                
                
