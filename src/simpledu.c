#include "simpledu.h"

int s_pid = 0;

int main(int argc, char const *argv[])
{
    /*
    signal(SIGINT, INTHandler);
    signal(SIGTSTP, TSTPHandler);
    signal(SIGCONT, CONTHandler);
    */

    simpledu *sd = createSimpledu();

    fillSimpledu(sd, argc, argv);
    printSimpledu(sd);

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
