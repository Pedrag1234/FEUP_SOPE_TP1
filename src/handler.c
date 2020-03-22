#include "handler.h"

int terminated = 0;

void initHandler(int signo)
{
    if (signo != SIGINT)
    {
        return;
    }

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

        printf("Resuming program\n");
        return;
    }
}
