#include "simpledu.h"

int main(int argc, char const *argv[])
{
    printf("Argc : %d | Argv = %s\n", argc, argv[0]);

    simpledu *sd = createSimpledu();

    fillSimpledu(sd, argc, argv);

    printSimpledu(sd);
    //printUsage();

    initFT();
    char directories[1024][256];
    char *cmdstring = malloc(sizeof(char *));
    int status;
    if (sd->max_depth == 0)
    {
        printDirectory(sd->path, sd);
    }
    else
    {
        unsigned numDir = searchDirectory(sd->path, directories);

        for (unsigned i = 0; i < numDir; i++)
        {
            pid_t pid;
            pid = fork();

            if (pid < 0)
            {
                printf("Failed fork");
                exit(-1);
            }
            else if (pid == 0)
            {
                if (directories[i] != NULL)
                {
                    buildCmdstring(sd, directories[i], cmdstring);

                    //reruns the program with the new cmd and a decremented depth
                    execl("/bin/sh", "/bin/sh", "-c", cmdstring, (char *)0);
                }

                //TODO: replace with exitProcess(0)
                exit(0);
            }
            else
            {
                waitpid(pid, &status, 0);

                //print path
                printf("%s\n", directories[i]);
            }
        }

        printDirectory(sd->path, sd);
    }

    destroySimpledu(sd);
    return 0;
}
