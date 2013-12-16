#include <stdio.h>
#include <string.h>

#define N 80

#define MIN(a, b) ((a)<(b) ? (a) : (b))
#define MAX(a, b) ((a)>(b) ? (a) : (b))

void swap(char *a, char *b)
{
	char ch;

	ch = *a;
	*a = *b;
	*b = ch;
}

void reverse(char *str)
{
	int len = strlen(str);
	int i;

	for (i=0; i<len/2; i++)
	{
		swap(&str[i], &str[len-i-1]);
	}
}

void add(char a[N], char b[N], char c[N+1])
{
	int i, m, n, min, max;
	char *p;

	memset(c, '0', N+1);

	m = strlen(a);
	n = strlen(b);

	min = MIN(m, n);
	max = MAX(m, n);

	p = m<=n ? a : b;
	for (i=0; i<min; i++)
		c[i] = p[min-i-1];

	p = m>n  ? a : b;
	for (i=0; i<max; i++)
	{
		if ((c[i] += p[max-i-1] - '0') > '9')
		{
			c[i] -= 10;
			c[i+1] += 1;
		}
	}

	if (c[max] == '0')
		c[max] = '\0';
	else
		c[max+1] = '\0';

	reverse(c);
}

int test()
{
	char *a[] = {"123456789",       "111111111111111", "83418201240", "23232", "123456"};
	char *b[] = {  "1036789", "111123209311111111911",   "831048347", "23232", "876545"};
	char c[N+1];
		 
	char *o[] = {"124493578", "111123320422222223022", "84249249587", "46464", "1000001"};

	int i;

	for (i=0; i<5; i++)
	{
		add(a[i], b[i], c);

		if (strcmp(o[i], c) == 0) 
		{
			printf("Success!\n");
		}
		else
		{
			printf("Error! %s + %s = %s\n", a[i], b[i], c);
			printf("\tBut the correct anwser is %s\n", o[i]);
		}

	}

}

int main()
{
	test();
	return 0;
}
