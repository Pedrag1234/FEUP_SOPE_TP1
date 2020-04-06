#include "filetreking.h"

#define READ 0
#define WRITE 1

void debug(int test)
{
    printf("Hello %d\n", test);
    test++;
}

unsigned depth(char * path)
{
    unsigned count = 0;
    for(unsigned i = 0; path[i] != '\0'; i++){
        if(path[i] == '/') count ++;
    }
    
    return count;
}

void printAll(simpledu * sd, Container * container)
{
    char * path;
    printf("%d\n", container->length);
    for(int i = 0; i < container->length; i++)
    {
        path = container->paths[i].path;
        if(depth(path) <= sd->max_depth)
        {
            int size = container->paths[i].info.st_size;
            if(sd->all_flag)
            {
                printFile(sd, path, size);
                printf("%d\n", depth(path));
            }
            else if(S_ISDIR(container->paths[i].info.st_mode))
            {
                printFile(sd, path, size);
                printf("%d\n", depth(path));
            }
        }
    }
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

int searchDirectory(char * dirPath, simpledu * sd, Container * container)
{
    DIR *myDir;
    struct dirent *info;
    struct stat pathStat;

    if (( myDir = opendir(sd->path)) == NULL)
    {
        printf("Error: cannot open provided directory: %s\n", sd->path);
        //replace with exitProcess(1)
        exit(1);
    }

    //new working directory
    chdir(sd->path);

    while ((info = readdir(myDir)) != NULL)
    {

        if(sd->deference_flag)
            stat(info->d_name, &pathStat);
        else
            lstat(info->d_name, &pathStat);

        //setup path to use
        char finalPath[256] = "";
        strcpy(finalPath, dirPath);
        strcat(finalPath, "/");
        strcat(finalPath, info->d_name);

        //regular file (.txt, .jpg, .c, etc)
        if(S_ISREG(pathStat.st_mode))
        {   
            //allocates space in array for new pathInfo entity
            if(container->length == container->size)
            {
                container->paths = realloc(container->paths, 2* container->size * sizeof(pathInfo));
                container->size *= 2;
            }

            //adds new entry to container and pathInfo simultaneously
            strcpy(container->paths[container->length].path, finalPath);
            container->paths[container->length].info = pathStat;
            container->length = container->length + 1;
            printf("%d\n", container->length);
        }
        //folders
        else if(S_ISDIR(pathStat.st_mode))
        {   
            //update with new path because of recursion
            strcpy(sd->path, info->d_name);

            //goes to next iter of the loop
            if( strcmp(info->d_name, ".") == 0 || strcmp(info->d_name, "..") == 0) continue;

            pid_t pids[256];
            unsigned pidCounter = 0;

            //setup read/write slots
            int slots[2];
            pipe(slots);
            
            //add createProcess() for logging here!!
            pids[pidCounter] = fork();

            if(pids[pidCounter] < 0)
            {
                printf("Error: could not fork.\n");
                //replace with exitProcess(-1)
                exit(-1);
            }
            //child
            else if (pids[pidCounter] == 0)
            {
                //recursiveness here (notice all args have already been updated previously)
                searchDirectory(finalPath, sd, container);

                close(slots[READ]);
                write(slots[WRITE], &container->size, sizeof(unsigned));
                write(slots[WRITE], container->paths, sizeof(pathInfo) * (container->size));
                
                //replace with exitProcess(0)
                exit(0);
            }
            else
            {
                //wait for pids to die
                int status;
                for (unsigned i = 0; i <= pidCounter; i++)
                    waitpid(pids[i], &status, 0);

                pidCounter++;

                int size;
                close(slots[WRITE]);
                read(slots[READ],&size,sizeof(int));
                
                while(size > container->size)
                {
                  container->paths = realloc(container->paths, 2 * container->size * sizeof(pathInfo));
                }

                container->paths = realloc(container->paths, size * sizeof(pathInfo));
                read(slots[READ], container->paths, sizeof(pathInfo) * size);
                container->size = size;
            }

            //allocates space in array for new pathInfo entity
            if(container->length == container->size)
            {
                container->paths = realloc(container->paths, 2* container->size * sizeof(pathInfo));
                container->size *= 2;
            }

            //adding THIS directory to array
            strcpy(container->paths[container->length].path, finalPath);
            container->paths[container->length].info = pathStat;
            container->length = container->length + 1;
            printf("%d\n", container->length);
        }
    }
    
    //repeats procces for above directory
    chdir("..");

    closedir(myDir);
    return 0;
}
