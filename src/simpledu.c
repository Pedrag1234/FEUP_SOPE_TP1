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

    //chdir(sd->path);

    Container paths;
    paths.size = 32;
    paths.paths = malloc(sizeof(pathInfo) * paths.size);
    paths.length = 0;

    searchDirectory(".", sd, &paths);

    printAll(sd, &paths);

    destroySimpledu(sd);
    free(paths.paths);

    return 0;
}
