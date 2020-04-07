#include "simpledu.h"

extern pid_t s_pid[1024];
extern int s_cnt;

int main(int argc, char const *argv[])
{

    signal(SIGINT, INTHandler);
    signal(SIGTSTP, TSTPHandler);
    signal(SIGCONT, CONTHandler);

    simpledu *sd = createSimpledu();

    fillSimpledu(sd, argc, argv);
    //printSimpledu(sd);

    Container info;
    info.objects = malloc(sizeof(pathInfo) * 32);
    info.length = 0;
    info.size = 32;

    searchDirectory(".", sd, &info);

    printAll(sd, &info);
    free(info.objects);
    destroySimpledu(sd);

    return 0;
}
