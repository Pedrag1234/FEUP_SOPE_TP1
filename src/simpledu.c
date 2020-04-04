#include "simpledu.h"

#define READ 0
#define WRITE 1

int main(int argc, char const *argv[])
{
    long folderSize = 0;

    printf("Argc : %d | Argv = %s\n", argc, argv[0]);

    simpledu *sd = createSimpledu();

    fillSimpledu(sd, argc, argv);

    //printSimpledu(sd);
    //printUsage();

    int slots[2];
    pipe(slots);

    char directories[1024][256];
    char *cmdstring = malloc(sizeof(char *));
    int status;
    if (sd->max_depth == 0)
    {
        printDirectory(sd->path, sd, &folderSize);
    }
    else
    {
        unsigned numDir = searchDirectory(sd->path, directories);
        char buf[1024];
        long subFolder;

        for (unsigned i = 0; i < numDir; i++)
        {
            pid_t pid;
            pid = fork();
            printf("%d", pid);

            if (pid < 0)
            {
                printf("Failed fork");
                exit(-1);
            }
            else if (pid == 0)
            {
                //creates copy of fd in slots[1]
                dup2(slots[WRITE], STDOUT_FILENO);
                close(slots[READ]);

                if (directories[i] != NULL)
                {

                    buildCmdstring(sd, directories[i], cmdstring);
                    //cmd_2_str(cmdstring, resp);
                    //reruns the program with the new cmd and a decremented depth
                    execl("/bin/sh", "/bin/sh", "-c", cmdstring, (char *)0);
                }

                //TODO: replace with exitProcess(0)
                exit(0);
            }
            else
            {
                close(slots[WRITE]);
                waitpid(pid, &status, 0);

                ssize_t len;
                while ((len = read(slots[READ], &buf, sizeof(buf))))
                {
                    printf("%s", buf);
                }

                //searches for the last newline escape char
                char *nbuf = strrchr(buf, '\n');
                nbuf = nbuf + 1;

                //exchange print for meaningful one
                printf("\nSize in last line - %s\n", nbuf);

                char *tok = strtok(nbuf, " \t\0");
                subFolder = atol(tok);
                printf("Size of subfolder - %ld\n", subFolder);
                folderSize = subFolder;

                //print path
                printf("%s\n", directories[i]);
            }
        }

        printDirectory(sd->path, sd, &folderSize);
    }

    destroySimpledu(sd);
    return 0;
}
