#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>


void str_cent_print(char *s)
{
#define WIDTH 32
    char str[WIDTH+1];
    int width;

    memset(str, sizeof(str), 0);

    width = (WIDTH + strlen(s)) / 2;
    snprintf(str, sizeof(str)-1, "%*s", width, s);
    printf("======== %*s ========\n", -WIDTH, str);
}

int main()
{

    char *p  =     "Hello, World!";
    char *p1 =  "1: Hello, World!";
    
    str_cent_print(p);
    str_cent_print(p1);

    return 0;
}

