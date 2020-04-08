#include "log.h"

int fd;
char fileName[256];
clock_t start;

void createFile()
{
    start = clock();

    if (getenv("LOG_FILENAME") == NULL)
        strcpy(fileName, DEFAULT);
    else
        strcpy(fileName, getenv("LOG_FILENAME"));

    fd = open(fileName, O_WRONLY | O_CREAT | O_APPEND);
    if (fd < 0)
    {
        perror("Error: file not found!\n");
        exit(1);
    }
}

void createProcess(const char **args)
{
    clock_t stop = clock();
    pid_t pid = getpid();
    float time = (stop - start) / (CLOCKS_PER_SEC / (double)1000.0);
    char log[256], cmd[256];

    while (*args)
    {
        char temp[256];
        strcpy(temp, *args++);
        strcat(temp, " ");
        strcat(cmd, temp);
    }
    sprintf(log, "%.2lf\t-\t%d\t-\tCREATE\t-\t%s\n", time, pid, cmd);
    write(fd, log, strlen(log));
}

void exitProcess(int exitStatus)
{
    clock_t stop = clock();
    pid_t pid = getpid();
    float time = (stop - start) / (CLOCKS_PER_SEC / (double)1000.0);
    char log[256];
    //instant - pid - EXIT - status
    sprintf(log, "%.2lf\t-\t%d\t-\tEXIT\t-\t%d\n", time, pid, exitStatus);
    write(fd, log, strlen(log));
}

void recieveSignal(int signal)
{
    clock_t stop = clock();
    pid_t pid = getpid();
    float time = (stop - start) / (CLOCKS_PER_SEC / (double)1000.0);
    char log[256];
    //instant - pid - RECV_SIGNAL - signal
    sprintf(log, "%.2lf\t-\t%d\t-\tRECV_SIGNAL\t-\t%d\n", time, pid, signal);
    write(fd, log, strlen(log));
}

void sendSignal(int signal, pid_t pid)
{
    clock_t stop = clock();
    pid_t pid2 = getpid();
    float time = (stop - start) / (CLOCKS_PER_SEC / (double)1000.0);
    char log[256];
    //instant - pid - SEND_SIGNAL - Signal signal sent to pid
    sprintf(log, "%.2lf\t-\t%d\t-\tRECV_SIGNAL\t-\tSignal %d sent to %d\n", time, pid2, signal, pid);
    write(fd, log, strlen(log));
}

void receivePipe(const char *pipemsg)
{
    clock_t stop = clock();
    pid_t pid = getpid();
    float time = (stop - start) / (CLOCKS_PER_SEC / (double)1000.0);
    char log[256];
    //instant - pid - RECV_PIPE - Message Received
    sprintf(log, "%.2lf\t-\t%d\t-\tRECV_PIPE\t-\tMessage received: %s\n", time, pid, pipemsg);
    write(fd, log, strlen(log));
}

void sendPipe(const char *pipemsg)
{
    clock_t stop = clock();
    pid_t pid = getpid();
    float time = (stop - start) / (CLOCKS_PER_SEC / (double)1000.0);
    char log[256];
    //instant - pid - SEND_PIPE - Message Received
    sprintf(log, "%.2lf\t-\t%d\t-\tRECV_PIPE\t-\tMessage sent: %s\n", time, pid, pipemsg);
    write(fd, log, strlen(log));
}

void entry(const char *entryRes)
{
    clock_t stop = clock();
    pid_t pid = getpid();
    float time = (stop - start) / (CLOCKS_PER_SEC / (double)1000.0);
    char log[256];
    //instant - pid - ENTRY - Bytes/Blocks followed by Path
    sprintf(log, "%.2lf\t-\t%d\t-\tENTRY\t-\t%s\n", time, pid, entryRes);
    write(fd, log, strlen(log));
}

void CloseFile()
{
    close(fd);
}