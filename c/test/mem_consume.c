#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

// ./proc max_mem mb_per_s
int main(int argc, char **argv)
{

    size_t size = 4096; //4K
    size_t max = 100*1024*1024; //100M
    size_t n;
    char *p;
    int step = 1000000; //1000ms
   
    if (argc > 1 )
    {
        n = 1024 * 1024 * atoi(argv[1]);
        if (n < max)
            max = n;
    }
    if (argc > 2 )
    {
        step = atoi(argv[2]); // M/s
    }

    if (step < 100 && step > 1)
    {
        step = 10000000/step;
    }

    n = 0;
    while (n < max)
    {
        do {
            p = (char *)malloc(size);
            if (NULL == p)
            {
                printf("malloc error!");
                exit(1);
            }
            n += size;
        } while ( 0 != n % (10*1024*1024));

        usleep(step);
    }

    while ( 1 )
    {
        usleep(step);
    }

    return 0;
}
