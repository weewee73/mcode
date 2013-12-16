#include <stdio.h>

void mprint(int i)
{
	int j;
	printf("\n");
	for (j=0; j<i; j++)
		printf(" -");
}

int mystrlen(char *buf, int N)
{
	static int i=0;
	int j;
	mprint(++i);
	printf("%s, N=%d ", buf, N);
	if (buf[0] == 0 || N == 0)
	{
		printf("^ ");
		mprint(--i);
		return 0;
	}
	else if (N == 1)
	{
		printf("^^ ");
		mprint(--i);
		return 1;
	}

	printf(". ");
	int k = mystrlen(buf, N/2);
	printf("k=%d ", k);
	if (k < N/2)
	{
		printf("^^ ");
		mprint(--i);
		return k;
	}
	else
	{
		printf(".. ");
		int t = mystrlen(buf+N/2, (N+1)/2);
		printf("t=%d ^^^ ", t);
		mprint(--i);
		return k + t;
	}
}

int main()
{
	char buf[] = {'a','b','c','d',0,'e','f','x','y','z', 0};
	int k;

	k = mystrlen(buf, 16);
	printf("\n%d\n", k);

	return 0;
}
