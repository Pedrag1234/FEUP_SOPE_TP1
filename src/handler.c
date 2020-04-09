#include "handler.h"

int terminated = 0;

pid_t s_pid[1024];
int s_cnt = 0;
int handlerflag = 0;

void INTAggregateHandler(int signo)
{
    if (handlerflag == 0)
        INTHandler2(signo);
    else
        INTHandler1(signo);
}

void INTHandler1(int signo)
{
    if (signo != SIGINT)
    {
        return;
    }

    for (size_t i = 0; i < 1024; i++)
    {
        if (s_pid[i] > 0)
        {
            sendSignal(SIGSTOP, s_pid[i]);
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
                sendSignal(SIGCONT, s_pid[i]);
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

void INTHandler2(int signo)
{
    if (signo != SIGINT)
    {
        return;
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
    recieveSignal(SIGTSTP);
    /*while (terminated != 1)
    {
       
    }*/
}

void CONTHandler(int signo)
{
    if (signo != SIGCONT)
    {
        return;
    }
    recieveSignal(SIGCONT);
}
