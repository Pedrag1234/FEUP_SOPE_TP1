#include "filetreking.h"

#define READ 0
#define WRITE 1

extern struct sigaction signals;
extern pid_t c_pid;
extern pid_t s_pid[1024];
extern int s_cnt;
extern int handlerflag;

int depth(char path[])
{
  int count = 0;
  for (int i = 0; path[i] != '\0'; i++)
  {
    if (path[i] == '/')
      count++;
  }
  return count;
}

void printAll(simpledu *sd, Container *container)
{
  char *path;
  for (int i = 0; i < container->length; i++)
  {
    path = container->objects[i].path;
    if (depth(path) <= sd->max_depth)
    {
      int size = container->objects[i].info.st_size;
      if (sd->all_flag)
        printFile(sd, path, size);
      else if (S_ISDIR(container->objects[i].info.st_mode))
        printFile(sd, path, size);
    }
  }
}

void printFile(simpledu *sd, char *path, long size)
{
  if (sd->byte_size_flag)
    printf("%-ld\t", size);
  else
  {
    //check if size is divisible by given block size
    size = size % sd->block_size == 0 ? size / sd->block_size : size / sd->block_size + 1;
    printf("%-ld\t", size);
  }

  printf("%s\n", path);
}

int searchDirectory(char *dirPath, simpledu *sd, Container *container)
{
  DIR *myDir;
  struct dirent *info;
  struct stat pathStat;

  //Installing INT handler
  signals.sa_handler = INTAggregateHandler;
  sigaction(SIGINT, &signals, NULL);

  myDir = opendir(sd->path);
  if (myDir == NULL)
  {
    printf("Error: unable to open directory %s", sd->path);
    exitProcess(1);
  }

  //change to new working directory (works better for recursiveness smh)
  chdir(sd->path);

  while ((info = readdir(myDir)) != NULL)
  {

    if (sd->deference_flag)
      lstat(info->d_name, &pathStat);
    else
      stat(info->d_name, &pathStat);

    //new path
    char finalPath[256] = "";
    strcat(finalPath, dirPath);
    strcat(finalPath, "/");
    strcat(finalPath, info->d_name);

    if (S_ISREG(pathStat.st_mode))
    {
      //allocate necessary space
      if (container->length == container->size)
      {
        container->objects = realloc(container->objects, 2 * container->size * sizeof(pathInfo));
        container->size *= 2;
      }

      strcpy(container->objects[container->length].path, finalPath);
      container->objects[container->length].info = pathStat;
      container->length += 1;
    }
    // Diretorios
    else if (S_ISDIR(pathStat.st_mode))
    {
      strcpy(sd->path, info->d_name); //update flag with path of directory we will analyse

      if ((strcmp(info->d_name, ".") == 0 || strcmp(info->d_name, "..") == 0))
        continue;

      pid_t pids[1024];
      int pCounter = 0, slots[2];
      pipe(slots);
      pids[pCounter] = fork();
      handlerflag = 1;
      if (pids[pCounter] > 0)
      {
        s_pid[s_cnt] = pids[pCounter];
        s_cnt++;
      }

      if (pids[pCounter] < 0)
      {
        printf("Error: could not fork %d\n", pCounter);
        exitProcess(1);
      }
      else if (pids[pCounter] == 0)
      {
        //Installing TSTP handler
        signals.sa_handler = TSTPHandler;
        sigaction(SIGTSTP, &signals, NULL);

        //Installing CONT handler
        signals.sa_handler = CONTHandler;
        sigaction(SIGCONT, &signals, NULL);

        searchDirectory(finalPath, sd, container);
        close(slots[READ]);

        //send info to father proc
        write(slots[WRITE], &container->length, sizeof(int));
        sendPipe("Address of container lenght");
        write(slots[WRITE], container->objects, sizeof(pathInfo) * (container->length));
        sendPipe("Array of objects of container");
        exitProcess(0);
      }
      else
      {
        int status;

        for (int i = 0; i <= pCounter; i++)
        {
          waitpid(pids[i], &status, 0); //waiting for each child to terminate
          sleep(1);
        }

        pCounter++;

        int index;
        close(slots[1]);
        read(slots[0], &index, sizeof(int));
        receivePipe("Address of container lenght");
        while (index > container->size)
          container->objects = realloc(container->objects, 2 * container->size * sizeof(pathInfo));

        //update information
        read(slots[0], container->objects, sizeof(pathInfo) * (index));
        receivePipe("Array of objects of container");
        container->length = index;
      }

      if (container->length == container->size)
      {
        container->objects = realloc(container->objects, 2 * container->size * sizeof(pathInfo));
        container->size *= 2;
      }

      //adding THIS directory to array
      strcpy(container->objects[container->length].path, finalPath);
      container->objects[container->length].info = pathStat;
      container->length += 1;
    }
  }

  chdir("..");
  closedir(myDir);
  return 0;
}