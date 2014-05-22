#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

// ./proc max_open speed
void  rm_handler(int  sig)
{
    system("rm -f /tmp/test_*");
    printf("\nrm test files.\r");
    exit(-1);
}

int main(int argc, char **argv)
{

    FILE *fp;
    char cmd[64], buffer[64];
    int cnt = 0, n, max = 20, step = 10000;

    sprintf(cmd, "lsof -p %d | wc -l", getpid());
    fp=popen(cmd, "r");
    fgets(buffer, sizeof(buffer), fp);
    cnt = atoi(buffer);

    if (argc > 1 )
    {
        n = atoi(argv[1]);
        if (n > max)
            max = n;
    }
    if (argc > 2 )
    {
        step = atoi(argv[2]); 
    }



    if (step < 100 && step > 0)
    {
        step = 1000000/step;
    }

    signal(SIGINT, rm_handler);


    while (cnt < max)
    {
        sprintf(buffer, "/tmp/test_%d", cnt++);
        if (NULL == (fp = fopen(buffer, "w+")))
        {
            printf("fopen error!");
            exit(1);
        }
        usleep(step);
    }
 
    while ( 1 )
    {
        usleep(step);
    }

    return 0;
}
