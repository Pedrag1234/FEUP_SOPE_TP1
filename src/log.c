#include "log.h"

FILE * file;
char fileName[256];
clock_t start;

void createFile()
{
    start = clock();

    if(getenv("LOG_FILENAME") == NULL)
        strcpy(fileName, DEFAULT);
    else
        strcpy(fileName, getenv("LOG_FILENAME"));

    file = fopen(fileName, "w");

    if(file == NULL)
    {
        perror("Error: file not found!\n");
        exit(1);
    }

}


void createProcess(const char ** args)
{
    clock_t stop = clock();
    pid_t pid = getpid();
    float time = fabs((stop - start)/(CLOCKS_PER_SEC / (double) 1000.0));

    //instant - pid - CREATE - args
    fprintf(file, "%.2lf\t-\t%d\t-\tCREATE\t\t-\t", time, pid);
    while (*args) fprintf(file, "%s ", *args++ );
    fprintf(file, "\n");

}

void exitProcess(int exitStatus)
{
    clock_t stop = clock();
    pid_t pid = getpid();
    float time = fabs((stop - start)/(CLOCKS_PER_SEC / (double) 1000.0));

    //instant - pid - EXIT - status
    fprintf(file, "%.2lf\t-\t%d\t-\tEXIT\t\t-\t%d\n", time, pid, exitStatus); 

    exit(exitStatus);
}

void recieveSignal(int signal)
{
    clock_t stop = clock();
    pid_t pid = getpid();
    float time = fabs((stop - start)/(CLOCKS_PER_SEC / (double) 1000.0));

    //instant - pid - RECV_SIGNAL - signal
    fprintf(file, "%.2lf\t-\t%d\t-\tRECV_SIGNAL\t-\t%d\n", time, pid, signal);

}

void sendSignal(int signal, pid_t pid)
{
    clock_t stop = clock();
    pid_t pid2 = getpid();
    float time = fabs((stop - start)/(CLOCKS_PER_SEC / (double) 1000.0));

    //instant - pid - SEND_SIGNAL - Signal signal sent to pid
    fprintf(file, "%.2lf\t-\t%d\t-\tRECV_SIGNAL\t-\tSignal %d sent to %d\n", time, pid2, signal, pid);
}

void receivePipe(const char *pipemsg)
{
    clock_t stop = clock();
    pid_t pid = getpid();
    float time = fabs((stop - start)/(CLOCKS_PER_SEC / (double) 1000.0));


    //instant - pid - RECV_PIPE - Message Received
    fprintf(file, "%.2lf\t-\t%d\t-\tRECV_PIPE\t-\tMessage received: %s\n", time, pid, pipemsg);
}

void sendPipe(const char *pipemsg)
{
    clock_t stop = clock();
    pid_t pid = getpid();
    float time = fabs((stop - start)/(CLOCKS_PER_SEC / (double) 1000.0));

    //instant - pid - SEND_PIPE - Message Received
    fprintf(file, "%.2lf\t-\t%d\t-\tSEND_PIPE\t-\tMessage sent: %s\n", time, pid, pipemsg);
}

void entry(const char *entryRes)
{
    clock_t stop = clock();
    pid_t pid = getpid();
    float time = fabs((stop - start)/(CLOCKS_PER_SEC / (double) 1000.0));

    //instant - pid - ENTRY - Bytes/Blocks followed by Path
    fprintf(file, "%.2lf\t-\t%d\t-\tENTRY\t-\t%s\n", time, pid, entryRes);
}

void CloseFile()
{
    fclose(file);
}