#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int
main(int argc, char *argv[])
{
    double course, count;
    course = atof(argv[1]);
    for (int i = 2; i < argc; i++){
        count = atof(argv[i]) + 100;
        course *= count * 100;
        int del = round(course);
        course = (double) del / 10000;
    }
    printf("%.4f\n", course);
}
