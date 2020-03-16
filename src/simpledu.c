#include "simpledu.h"

int main(int argc, char const *argv[])
{
    printf("Argc : %d | Argv = %s\n", argc, argv[0]);

    simpledu *sd = createSimpledu();

    printSimpledu(sd);

    destroySimpledu(sd);

    return 0;
}

simpledu *createSimpledu()
{
    simpledu *sd = (simpledu *)malloc(sizeof(simpledu));

    sd->count_links_flag = 1;
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

void destroySimpledu(simpledu *sd)
{
    if (sd == NULL)
    {
        return;
    }

    free(sd);
}