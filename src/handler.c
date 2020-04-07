#include "handler.h"

int terminated = 0;

pid_t s_pid[1024];
int s_cnt = 0;

void INTHandler(int signo)
{
    if (signo != SIGINT)
    {
        return;
    }

    for (size_t i = 0; i < 1024; i++)
    {
        if (s_pid[i] > 0)
        {
            kill(s_pid[i], SIGTSTP);
        }
        else
        {
            break;
        }
    }

    char c;
    printf("Are you sure you want to exit? (Y)es/(N)o\n");
    fflush(stdin);
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
        exit(0);
    }

    else if (toupper(c) == 'N')
    {

        for (size_t i = 0; i < 1024; i++)
        {
            if (s_pid[i] > 0)
            {
                kill(s_pid[i], SIGCONT);
            }
            else
            {
                break;
            }
        }
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
