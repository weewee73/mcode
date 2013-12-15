#include <stdio.h>
#include <string.h>

void swap(char *a, char *b)
{
	char temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

int gcd(int a, int b)
{
	int c;

	while (a % b != 0)
	{
		c = a % b;
		a = b;
		b = c;
	}

	return b;
}

int gcd_1(int a, int b)
{
	while (a != b)
	{
		if (a > b)
			a -= b;
		else
			b -= a;
	}

	return a;
}

void reverse(char a[], int start, int end)
{
	char *p = a + start;
	char *q = a + end;

	for ( ; p<q; p++,q--)
		swap(p, q);
}

void rotate(char a[], int n, int m)
{
	//ab --> a^b^ --> (a^b^)^==ba
	if (m <= n)
	{
		reverse(a, 0, m-1);
		reverse(a, m, n-1);
		reverse(a, 0, n-1);
	}
}
void rotate_1(char a[], int n, int m)
{
	//circle
	char temp;
	int i, j, k;

	for (i=0; i<gcd(n, m); i++)
	{
		temp = a[i];
		j = i;
		while(1)
		{
			k = (j + m) % n;
			if (k == i)
				break;
			a[j] = a[k];
			j = k;
		}
		a[j] = temp;
	}
}

void test()
{
	char *in = "adieowfifjkdfd";
	int len = strlen(in);

	char *o[] = {"dieowfifjkdfda",
				 "ieowfifjkdfdad",
				 "eowfifjkdfdadi",
				 "owfifjkdfdadie",
				 "wfifjkdfdadieo",
				 "fifjkdfdadieow",
				 "ifjkdfdadieowf",
				 "fjkdfdadieowfi",
				 "jkdfdadieowfif",
				 "kdfdadieowfifj",
				 "dfdadieowfifjk",
				 "fdadieowfifjkd",
				 "dadieowfifjkdf",
				 "adieowfifjkdfd"
	            };

	int i;
	char a[100];

	printf("prime string: %s\n", in);
	for (i=0; i<len; i++)
	{
		strcpy(a, in);
		//rotate(a, len, i+1);
		rotate_1(a, len, i+1);
		if (strcmp(a, o[i]) == 0)
		{
			printf("Success! after rotate %2d: %s\n", i+1, a);
		}
		else
		{
			printf("Error!\n");
			printf("\tafter rotate %2d:          %s\n", i+1, a);
			printf("\tBut the correct anwser is %s\n", o[i]);
		}
	}
}

int main()
{
	test();
	return 0;
}
