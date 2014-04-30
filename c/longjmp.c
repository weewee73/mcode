#include <stdio.h>
#include <signal.h>
#include <setjmp.h>
#include <unistd.h>
#include <stdlib.h>

jmp_buf  JumpBuffer;

void     INThandler(int);

int  main(void)
{
    signal(SIGQUIT, INThandler);

    while (1) {
        if (setjmp(JumpBuffer) == 0) {
            printf("Hit Ctrl-\\ at anytime ... \n");
            pause();
        }
    }
}

void  INThandler(int  sig)
{
    char  c;

    signal(sig, SIG_IGN);
    printf("OUCH, did you hit Ctrl-\\?\n"
            "Do you really want to quit? [y/n] ");
    c = getchar();
    if (c == 'y' || c == 'Y')
        exit(0);
    else {
        signal(SIGQUIT, INThandler);
        longjmp(JumpBuffer, 0);
    }
}
