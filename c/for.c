#include <stdio.h>

int main()
{
    int i;
    
    for (i=0; ; i++)
    {
        printf("%d ", i);
        fflush(NULL);
    }
    return 0;
}
