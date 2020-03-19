#include "simpledu.h"

int main(int argc, char const *argv[])
{
    printf("Argc : %d | Argv = %s\n", argc, argv[0]);

    simpledu *sd = createSimpledu();

    fillSimpledu(sd, argc, argv);

    printSimpledu(sd);
    //printUsage();

    destroySimpledu(sd);

    return 0;
}

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

int isPath(const char *path)
{
    if (strcmp(path, ALL) != 0 && strcmp(path, BYTES) != 0 && strcmp(path, BLOCK_SIZE) != 0 && isNumber(path) != 0 && strcmp(path, SY_LINKS) != 0 && strcmp(path, SEP_DIRS) && strstr(path, MAX_DEPTH) == NULL)
        return 0;

    return 1;
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
        subString(string, 12, strlen(string) - strlen(MAX_DEPTH), number);

        //Remover este printf faz com que a funçaõ deixe de funcionar
        printf("Number=> (%s,%ld)|| isNumber = %d\n", number, strlen(number), isNumber(number));

        if (isNumber(number) == 0)
        {
            printf("Number = %s\n", number);
            return atoi(number);
        }
        else
        {
            return -1;
        }
    }
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
                if (isPath(argv[i]) == 0 && i == 2)
                    strcpy(sd->path, argv[i]);

                else if (strcmp(argv[i], ALL) == 0)
                    sd->all_flag = 1;

                else if (strcmp(argv[i], BYTES) == 0)
                    sd->byte_size_flag = 1;

                else if (strcmp(argv[i], BLOCK_SIZE) == 0)
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
        return 0;
    }
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