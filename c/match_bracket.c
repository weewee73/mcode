#include <stdio.h>
#include <string.h>

int main()
{
	char exp[1024];
	int x = 0, y = 0, z = 0, len = 0, i;

	scanf("%s", exp);
	len = strlen(exp);

	printf("%s, len=%d\n", exp, len);
	
	
	for (i=0; i<len; i++)
	{
		switch (exp[i])
		{
			case '(': ++x; break;
			case ')': --x; break;
			case '[': ++y; break;
			case ']': --y; break;
			case '{': ++z; break;
			case '}': --z; break;
			default: break;
		}
		if (x < 0 || y < 0 || z < 0)
			break;
	}

	if (x == 0 && y == 0 && z == 0)
		printf("Matched!");
	else
		printf("Not Matched!");

	return 0;
}
