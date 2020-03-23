#include "handler.h"

int terminated = 0;
extern int s_pid;

void INTHandler(int signo)
{
    if (signo != SIGINT)
    {
        return;
    }

    kill(s_pid, SIGTSTP);

    char c;
    printf("Are you sure you want to exit? (Y)es/(N)o\n");
    c = getchar();
    while (toupper(c) != 'Y' && toupper(c) != 'N')
    {
        fflush(stdin);
        printf("Are you sure you want to exit? (Y)es/(N)o\n");
        c = getchar();
    }

    if (toupper(c) == 'Y')
    {
        terminated = 1;
        printf("Exiting\n");
        return;
    }

    else if (toupper(c) == 'N')
    {
        kill(s_pid, SIGCONT);
        printf("Resuming program\n");
        return;
    }
}

void TSTPHandler(int signo)
{
    if (signo != SIGTSTP)
    {
        return;
    }
    printf("[caught SIGTSTP]\n");
}

void CONTHandler(int signo)
{
    if (signo != SIGCONT)
    {
        return;
    }
    printf("[caught SIGCONT]\n");
}
