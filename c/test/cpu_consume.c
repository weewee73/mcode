#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

// On a 32-bit system where CLOCKS_PER_SEC equals 1000000
// ./proc  percent speed
int main(int argc, char **argv)
{
    int busy = 10000; //10ms
    int idle = busy*2;
    int min = 0;
    int step = 10;
    int percent = 50; //50%
    clock_t start;

    if (argc > 1 )
    {
        percent = atoi(argv[1]);
    }
    if (argc > 2 )
    {
        step = atoi(argv[2]);
    }

    if (step > 100 || step < 1)
    {
        step = 10;
    }
    if (percent > 100 || percent < 1)
    {
        percent = 50;
    }

    min = (int)1.0*(100-percent)*busy / percent;
   
    while (1)
    {
        start = clock();
        while (0 > 1.0*(clock() - start)/CLOCKS_PER_SEC*1000*1000 - busy)
            ;
        if (idle > min)
            idle -= step;
        if (idle > 0)
            usleep(idle);
    }

    return 0;
}
