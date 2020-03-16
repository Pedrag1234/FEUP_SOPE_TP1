#ifndef _SIMPLEDU_H_
#define _SIMPLEDU_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH_LENGTH 256

typedef struct
{
    int count_links_flag;
    char path[MAX_PATH_LENGTH];
    int all_flag;
    int byte_size_flag;
    int block_size_flag;
    unsigned int block_size;
    int deference_flag;
    int directory_flag;
    int max_depth_flag;
    unsigned int max_depth;
} simpledu;

simpledu *createSimpledu();

void printSimpledu(simpledu *sd);

int fillSimpledu(simpledu *sd);

void destroySimpledu(simpledu *sd);

#endif
