#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLEN 15 

typedef enum
{
	IP_A = 0,
	IP_B,
	IP_C,
	IP_D,
	IP_E,
	IP_NO
}w;

w m(char *s)
{
	int m;
	w type;

	m = atoi(s);

	if (m >> 7 == 0x00)
		type = IP_A;
	else if (m >> 6 == 0x02)
		type = IP_B;
	else if (m >> 5 == 0x06)
		type = IP_C;
	else if (m >> 4 == 0x0E)
		type = IP_D;
	else if (m >> 3 == 0x1E)
		type = IP_E;
	else
	 	type = IP_NO;

	return type;
}

test()
{
	char *ip[] = {"192.168.1.110",
	              "115.239.210.151",
				  "399.181.112.25",
				  "180.149.132.165",
				  "226.181.112.25",
				  "244.149.132.165",
				  "74.125.235.193"};
		 
	w c;
	w o[] = {IP_C, 
	          IP_A,
	          IP_NO,
	          IP_B,
	          IP_D,
	          IP_E,
	          IP_A};

	int i;

	for (i=0; i<7; i++)
	{
		c = m(ip[i]);
		if (o[i] == c) 
		{
			printf("Success!\n");
		}
		else
		{
			printf("Error! ip:%s is %c class.\n", ip[i], c+'A');
			printf("\tBut the correct anwser is %c\n", o[i]+'A');
		}

	}

}


int main()
{
	test();
	return 0;
}
