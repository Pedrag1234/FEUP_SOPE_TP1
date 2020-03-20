#include "log.h"

FILE * file;

void createFile()
{
    char fileName[256];

    if(getenv("LOG_FILENAME") == NULL)
        strcpy(fileName, DEFAULT);
    else
        strcpy(fileName, getenv("LOG_FILENAME"));

    file = fopen(fileName, "w");
    fclose(file);
}


void createProcess(struct timeval mainStart, pid_t pid, const char ** args)
{
    char fileName[256];

    if(getenv("LOG_FILENAME") == NULL)
        strcpy(fileName, DEFAULT);
    else
        strcpy(fileName, getenv("LOG_FILENAME"));

    file = fopen(fileName, "a");

    //ms from start
    struct timeval stop;
    gettimeofday(&stop, NULL);
    float time = (stop.tv_sec - mainStart.tv_sec) * 1000000 + stop.tv_usec - mainStart.tv_usec;

    //instant - pid - CREATE - args
    fprintf(file, "%.2lf\t-\t%d\t-\tCREATE\t-\t", time, pid);
    while (*args) fprintf(file, "%s ", *args++ );
    fprintf(file, "\n");

    fclose(file);
}