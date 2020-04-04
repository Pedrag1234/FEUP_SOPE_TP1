#include "simpledu.h"

#define READ 0
#define WRITE 1


int s_pid = 0;
extern long folderSize;

int main(int argc, char const *argv[])
{

    signal(SIGINT, INTHandler);
    signal(SIGTSTP, TSTPHandler);
    signal(SIGCONT, CONTHandler);

    simpledu *sd = createSimpledu();

    fillSimpledu(sd, argc, argv);

    int slots[2];
    pipe(slots);

    char directories[1024][256];
    char *cmdstring = malloc(sizeof(char *));
    int status;
    if (sd->max_depth == 0)
    {
        printDirectory(sd->path, sd);
        exit(0);
    }
    else
    {
        int numDir = searchDirectory(sd->path, directories);
        char buf[1024];
        //long subFolder;

        for (int i = 0; i < numDir; i++)
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
                //creates copy of fd in slots[1]
                s_pid = pid;
                dup2(slots[WRITE], STDOUT_FILENO);
                close(slots[READ]);
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
                close(slots[WRITE]);
                while(waitpid(pid, &status, 0) > 0);

                ssize_t len;
                while ((len = read(slots[READ], &buf, sizeof(buf))))
                {
                    printf("%s", buf);
                }

                /*
                buf[len] = '\0';
                //searches for the last newline escape char
                char *nbuf = strrchr(buf, '\n');
                char * new_buf = nbuf + 1;

                //exchange print for meaningful one
                printf("\nSize in last line - %s\n", new_buf);

                char *tok = strtok(new_buf, " \t\0");
                subFolder = atol(tok);
                printf("Size of subfolder - %ld\n", subFolder);
                folderSize = subFolder;
                */

                //print path
                printf("%s\n", directories[i]);
            }
        }
        
        printDirectory(sd->path, sd);
        printf("%ld\n", folderSize);
    }

    destroySimpledu(sd);
    return 0;
}
