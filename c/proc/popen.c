/*取得当前目录下的文件个数*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>

#define MAXLINE 1024

int main()
{
	char result_buf[MAXLINE], command[MAXLINE];
	int rc = 0; // 用于接收命令返回值
	FILE *fp;

	/*将要执行的命令写入buf*/
	snprintf(command, sizeof(command), "sleep 2 && ls ./  abc");

	/*执行预先设定的命令，并读出该命令的标准输出*/
	fp = popen(command, "r");
	rc = pclose(fp);
    printf("命令【%s】子进程结束状态【%d】命令返回值【%d】\r\n", command, rc, WEXITSTATUS(rc));
    exit(0);
	if(NULL == fp)
	{
		perror("popen执行失败！");
		exit(1);
	}
	while(fgets(result_buf, sizeof(result_buf), fp) != NULL)
	{
		/*为了下面输出好看些，把命令返回的换行符去掉*/
		if('\n' == result_buf[strlen(result_buf)-1])
		{
			result_buf[strlen(result_buf)-1] = '\0';
		}
		printf("命令【%s】 输出【%s】\r\n", command, result_buf);
	}

	/*等待命令执行完毕并关闭管道及文件指针*/
	rc = pclose(fp);
	if(-1 == rc)
	{
		perror("关闭文件指针失败");
		exit(1);
	}
	else
	{
		printf("命令【%s】子进程结束状态【%d】命令返回值【%d】\r\n", command, rc, WEXITSTATUS(rc));
	}

	return 0;
}
