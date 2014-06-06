#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int daemon_init(void)
{
    pid_t pid;
    int i, fd;

    if ( (pid = fork()) < 0)
        return (-1);
    else if (pid != 0)
        exit(0);     /* parent goes bye-bye */

    /* child continues */
    setsid();       /* become session leader */
    chdir("/");     /* change working directory */
    umask(0);       /* clear our file mode creation mask */

    for (i=getdtablesize(); i>=0; --i)
        close(i); /* close all descriptors */ 

    /* The file descriptor returned by a successful call will be the lowest-numbered file descriptor not currently open for the process. */
    /* So fd=0 STDIN_FILENO */
    fd = open("/dev/null", O_RDWR);
    dup2(fd, STDOUT_FILENO);
    dup2(fd, STDERR_FILENO);

    return (0);
}


int main()
{
    daemon_init();

    /* do something */
    sleep(99999999);

    return 0;
}
