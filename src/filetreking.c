#include "filetreking.h"

void initFT()
{
    folderSize = 0;
}

void printFile(simpledu *sd, char *path, long size)
{
    //check if print in bytes
    if (sd->byte_size_flag)
        printf("%ld\t", size);
    else
    {
        //check if size is divisible by given block size
        size = size % sd->block_size == 0 ? size / sd->block_size : size / sd->block_size + 1;
        printf("%ld\t", size);
    }

    printf("%s\n", path);
}

int searchFile(simpledu *sd, char *fileName)
{
    struct stat file;
    char buf[1024];
    //signed size type, capable of holding -1 in case of errors
    ssize_t len;

    if (stat(fileName, &file) < 0)
    {
        perror("Error reading file stat struct");
        //replace with exitProcess(1) when importing log.h
        exit(1);
    }

    //handling symbolic stuff
    if (isPath(fileName) == 2 && sd->deference_flag)
    {
        lstat(fileName, &file);
        if ((len = readlink(fileName, buf, sizeof(buf) - 1)) != -1)
        {
            //null terminator
            buf[len] = '\0';
            strcat(fileName, "/");
            strcat(fileName, buf);
        }
        else
            perror("Error in reading symbolic link");
    }

    printFile(sd, fileName, file.st_size);
    folderSize += file.st_size;

    return 0;
}

int searchDirectory(char *path, char direct[1024][256])
{
    DIR *myDir;
    struct dirent *info;
    char finalPath[256];

    int numDir = 0;
    myDir = opendir(path);
    if (myDir == NULL)
    {
        perror("Error: cannot open provided directory");
        //replace with exitProcess(1)
        exit(1);
    }

    while ((info = readdir(myDir)) != 0)
    {
        //setup path to use
        strcpy(finalPath, path);
        strcat(finalPath, "/");
        strcat(finalPath, info->d_name);

        if (isPath(finalPath) == 1 && strcmp(info->d_name, ".") && strcmp(info->d_name, ".."))
        {
            strcpy(direct[numDir], finalPath);
            numDir++;
        }
    }

    closedir(myDir);
    return numDir;
}

void printDirectory(char *path, simpledu *sd)
{
    DIR *myDir;
    struct dirent *info;
    char finalPath[256];

    myDir = opendir(path);
    if (myDir == NULL)
    {
        perror("Error: cannot open provided directory");
        //replace with exitProcess(1)
        exit(1);
    }

    while ((info = readdir(myDir)) != 0)
    {
        strcpy(finalPath, path);
        strcat(finalPath, "/");
        strcat(finalPath, info->d_name);

        if (isPath(finalPath) == 2 || isPath(finalPath) == 0)
        {
            searchFile(sd, finalPath);
        }
    }

    closedir(myDir);
}

void buildCmdstring(simpledu *sd, char *path, char *cmdstring)
{
    char cmd[256];
    char buf[256];

    strncpy(cmd, "./simpledu -l ", sizeof("./simpledu -l "));
    strcat(cmd, path);

    if (sd->all_flag)
    {
        strcat(cmd, " -a");
    }
    if (sd->byte_size_flag)
    {
        strcat(cmd, " -b");
    }
    if (sd->block_size_flag)
    {
        strcat(cmd, " -B ");
        sprintf(buf, "%d", sd->block_size);
        strcat(cmd, buf);
    }
    if (sd->count_links_flag)
    {
        strcat(cmd, " -l");
    }
    if (sd->deference_flag)
    {
        strcat(cmd, " -L");
    }
    if (sd->directory_flag)
    {
        strcat(cmd, " -S");
    }
    if (sd->max_depth > 0)
    {
        strcat(cmd, " --max-depth=");
        sprintf(buf, "%d", sd->max_depth - 1);
        strcat(cmd, buf);
    }

    strcpy(cmdstring, cmd);
}
