#include "simpledu.h"
#include "log.h"

struct sigaction signals;
pid_t c_pid;
extern pid_t s_pid[1024];
extern int s_cnt;

int main(int argc, char const *argv[])
{
    createFile();
    //
    sigemptyset(&signals.sa_mask);
    signals.sa_flags = 0;

    c_pid = getpid();

    simpledu *sd = createSimpledu();

    fillSimpledu(sd, argc, argv);
    printSimpledu(sd);

    Container info;
    info.objects = malloc(sizeof(pathInfo) * 32);
    info.length = 0;
    info.size = 32;
    createProcess(argv);
    searchDirectory(".", sd, &info);

    printAll(sd, &info);
    free(info.objects);
    destroySimpledu(sd);

    CloseFile();
    exitProcess(0);
}
