#include "simpledu.h"

int main(int argc, char const *argv[])
{
    printf("Argc : %d | Argv = %s\n", argc, argv[0]);

    simpledu *sd = createSimpledu();

    //printSimpledu(sd);
    //printUsage();
    printf("Is %s path? It's %d\n", ALL, isPath(ALL));
    printf("Is %s path? It's %d\n", BYTES, isPath(BYTES));
    printf("Is %s path? It's %d\n", BLOCK_SIZE, isPath(BLOCK_SIZE));
    printf("Is %s path? It's %d\n", SY_LINKS, isPath(SY_LINKS));
    printf("Is %s path? It's %d\n", SEP_DIRS, isPath(SEP_DIRS));
    printf("Is %s path? It's %d\n", MAX_DEPTH, isPath(MAX_DEPTH));
    printf("Is %s path? It's %d\n", "123654", isPath("123654"));
    printf("Is %s path? It's %d\n", "mYmilkShake", isPath("mYmilkShake"));

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

int isPath(char *path)
{
    if (strcmp(path, ALL) != 0 && strcmp(path, BYTES) != 0 && strcmp(path, BLOCK_SIZE) != 0 && isNumber(path) != 0 && strcmp(path, SY_LINKS) != 0 && strcmp(path, SEP_DIRS) && strstr(path, MAX_DEPTH) == NULL)
        return 0;

    return 1;
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
                {
                    strcpy(sd->path, argv[i]);
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