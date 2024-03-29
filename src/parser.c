#include "parser.h"

simpledu *createSimpledu()
{
    simpledu *sd = (simpledu *)malloc(sizeof(simpledu));

    sd->count_links_flag = 0;
    sd->all_flag = 0;
    sd->block_size_flag = 0;
    sd->byte_size_flag = 0;
    sd->deference_flag = 0;
    sd->directory_flag = 0;
    sd->max_depth_flag = 0;
    strcpy(sd->path, "");
    sd->max_depth = 0;
    sd->block_size = 0;

    return sd;
}

void printSimpledu(simpledu *sd)
{
    printf("Count link flag = %d\n", sd->count_links_flag);
    printf("Path = %s\n", sd->path);
    printf("All flag = %d\n", sd->all_flag);
    printf("Byte size flag = %d\n", sd->byte_size_flag);
    printf("Block size flag = %d | Block size = %d\n",
           sd->block_size_flag, sd->block_size);
    printf("Deference flag = %d\n", sd->deference_flag);
    printf("Separate dirs flag = %d\n", sd->directory_flag);
    printf("Max Depth flag = %d | Max depth = %d\n",
           sd->max_depth_flag, sd->max_depth);
}

int fillSimpledu(simpledu *sd, int argc, char const *argv[])
{
    if (argc < 2)
    {
        printUsage();
        return 1;
    }
    else
    {
        if (strcmp(argv[1], C_LINKS) != 0)
        {
            printUsage();
            return 1;
        }
        else
        {
            sd->count_links_flag = 1;

            for (int i = 2; i < argc; i++)
            {
                if (isPath(argv[i]) >= 0 && i == 2)
                    strcpy(sd->path, argv[i]);

                else if (strcmp(argv[i], ALL) == 0)
                    sd->all_flag = 1;

                else if (strcmp(argv[i], BYTES) == 0 && sd->block_size_flag != 1)
                    sd->byte_size_flag = 1;

                else if (strcmp(argv[i], BLOCK_SIZE) == 0 && sd->byte_size_flag != 1)
                {
                    sd->block_size_flag = 1;

                    if ((i + 1 >= argc) || isNumber(argv[i + 1]) != 0)
                    {
                        printUsage();
                        return 1;
                    }

                    else
                        sd->block_size = atoi(argv[i + 1]);
                }

                else if (strcmp(argv[i], SY_LINKS) == 0)
                    sd->deference_flag = 1;

                else if (strcmp(argv[i], SEP_DIRS) == 0)
                    sd->directory_flag = 1;

                else if (strstr(argv[i], MAX_DEPTH) != NULL)
                {
                    sd->max_depth_flag = 1;

                    int j = getMaxDepth(argv[i]);

                    if (j < 0)
                    {
                        printUsage();
                        return 1;
                    }
                    else
                    {
                        sd->max_depth = j;
                    }
                }
            }
        }
        if (sd->block_size_flag == 0 && sd->byte_size_flag == 0)
        {
            sd->block_size_flag = 1;
            sd->block_size = 1024;
        }
        if (strlen(sd->path) == 0)
        {
            strcpy(sd->path, ".");
        }

        return 0;
    }
}

void destroySimpledu(simpledu *sd)
{
    if (sd == NULL)
    {
        return;
    }

    free(sd);
}

void printUsage()
{
    printf("Usage: ./simpledu -l <path> <-a|-all> <-b|-bytes> <-B size|--block-size=SIZE> <-L|--count-links> <-S|--separate dirs> <--max-depth=N>\n");
}

int isPath(const char *path)
{
    struct stat pathStat;

    // Invalid path
    if (lstat(path, &pathStat) < 0)
        return -1;
    // Directory
    else if (S_ISDIR(pathStat.st_mode))
        return 1;
    // File
    else if (S_ISREG(pathStat.st_mode))
        return 0;
    // Symbolic Link
    else if (S_ISLNK(pathStat.st_mode))
        return 2;
    else
        return -1;
}

int getMaxDepth(const char *string)
{
    if (strlen(string) <= strlen(MAX_DEPTH))
    {
        return -1;
    }
    else
    {
        char number[26];
        strcpy(number, "");
        int i = strlen(MAX_DEPTH);
        //printf("%c\n", string[i]);

        while (string[i] >= '0' && string[i] <= '9')
        {
            char temp[1];

            temp[0] = string[i];

            strcat(number, temp);
            i++;
        }

        //printf("%s\n", number);
        //Remover este printf faz com que a funçaõ deixe de funcionar
        //printf("Number=> (%s,%ld)|| isNumber = %d\n", number, strlen(number), isNumber(number));

        if (isNumber(number) == 0)
        {
            //printf("Number = %s\n", number);
            return atoi(number);
        }
        else
        {
            return -1;
        }
    }
}
