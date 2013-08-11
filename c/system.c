#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

typedef void (*sighandler_t)(int);

int main()
{
	int ret = 0;
	extern int errno;
	sighandler_t old_handler;
	FILE *fp;

	fp = fopen("/log/yyyy.log", "w+");

	old_handler = signal(SIGCHLD, SIG_DFL);
	ret = system("/usr/local/xxx/ruby/bin/ruby  /usr/local/xxx/dpsploit/msfconsole -q -r /log/exploit/set_path_16.txt -o /log/exploit/result_path_16.txt");
    
	if (WIFEXITED(ret)) {
		fprintf(fp, "exited, status=%d\n", WEXITSTATUS(ret));
	}
	if (WIFSIGNALED(ret)) {
		fprintf(fp, "killed by signal %d\n", WTERMSIG(ret));
	}
	if (WIFSTOPPED(ret)) {
		fprintf(fp, "stopped by signal %d\n", WSTOPSIG(ret));
	}
	if (WIFCONTINUED(ret)) {
		fprintf(fp, "continued\n");
	}
	fprintf(fp, "ret=%d    errno=%d    status=%d\n", ret, errno, WEXITSTATUS(ret));
	signal(SIGCHLD, old_handler);

	fclose(fp);


	return ret;

}
