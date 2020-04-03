#include "simpledu.h"

int main(int argc, char const *argv[])
{
    //printf("Argc : %d | Argv = %s\n", argc, argv[0]);

    char resp[256];
    strcpy(resp, "");

    simpledu *sd = createSimpledu();

    fillSimpledu(sd, argc, argv);

    mkfifo(FIFO_PATH, 0666);

    initFT();
    char directories[1024][256];
    char *cmdstring = malloc(sizeof(char *));
    int status;
    if (sd->max_depth == 0)
    {
        long f_size = printDirectory(sd->path, sd);

        char str[256];
        sprintf(str, "%ld", f_size);

        int fd = open(FIFO_PATH, O_WRONLY);
        write(fd, str, 256);

        close(fd);
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
                    //cmd_2_str(cmdstring, resp);
                    //printf("Copy = %s\n", resp);
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
                char str[256];
                int fd = open(FIFO_PATH, O_RDONLY);
                read(fd, str, sizeof(str));
                close(fd);

                long f_size = atol(str);

                printf("%ld\t%s\n", f_size, directories[i]);
                //printf("%s\n", directories[i]);
            }
        }
        printDirectory(sd->path, sd);
    }

    destroySimpledu(sd);
    return 0;
}
