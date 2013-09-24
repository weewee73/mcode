#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>

int kbhit()
{
	int i;

	if (ioctl(0, FIONREAD, &i) < 0)
	{
		printf("Error!\n");
		return 0;
	}

	return i;
}

int main()
{
	int i = 0;
	char c = '^';

	printf("enter 'q' to quit \r\n");

	system("stty raw -echo");
	while (c != 'q'){
		if (kbhit()) {
			c = getchar();
			printf(" on iteration %d, got %c\r\n", i++, c);
		}
	}
	system("stty cooked echo");
}
