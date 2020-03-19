#include "simpledu.h"

int main(int argc, char const *argv[])
{
    printf("Argc : %d | Argv = %s\n", argc, argv[0]);

    simpledu *sd = createSimpledu();

    //printSimpledu(sd);
    //printUsage();
    printf("Is number: %d\n", isNumber("14253"));
    printf("Is number: %d\n", isNumber("Atomate"));
    printf("Is number: %d\n", isNumber("12eu1peixe"));

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

int isNumber(char *string)
{
    int s_size = strlen(string);

    for (int i = 0; i < s_size; i++)
    {
        //printf("Char %c and isDigit %d\n", string[i], isdigit(string[i]));
        if (isdigit(string[i]) == 0)
            return 1;
    }
    return 0;
}

/*int isPath(char *path, int i)
{
    if (i == 2 && strcmp(path, ALL) != 0 && strcmp(path, BYTES) != 0 && strcmp(path, BLOCK_SIZE) != 0 &&)
}*/

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