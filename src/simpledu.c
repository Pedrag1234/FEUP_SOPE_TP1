#include "simpledu.h"

int main(int argc, char const *argv[])
{
    printf("Argc : %d | Argv = %s\n", argc, argv[0]);

    simpledu *sd = createSimpledu();

    fillSimpledu(sd, argc, argv);

    printSimpledu(sd);
    //printUsage();

    destroySimpledu(sd);

    return 0;
}
