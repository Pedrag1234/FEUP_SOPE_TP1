#ifndef _PARSER_H_
#define _PARSER_H_

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"

#define MAX_PATH_LENGTH 256

#define ALL "-a"
#define BYTES "-b"
#define BLOCK_SIZE "-B"
#define C_LINKS "-l"
#define SY_LINKS "-L"
#define SEP_DIRS "-S"
#define MAX_DEPTH "--max-depth="

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

/** 
* @brief: Creates an instance of the struct simpledu
*
* @returns: A pointer to the created struct
*/
simpledu *createSimpledu();

/**
* @brief: Prints the contents of a simpledu struct 
*/
void printSimpledu(simpledu *sd);

/**
 * @brief: Parses the arguments from the console to a simpledu struct
 * 
 * @todo: finish parsing the other elements past -l 
 * 
 * @param sd: The struct to be filled
 * @param argc: The amount of arguments of the console
 * @param argv: The strings of those same arguments
 * 
 * @return: Returns 0 if successful and 1 if not  
 */
int fillSimpledu(simpledu *sd, int argc, char const *argv[]);

/**
 * @brief: Destroys an instance of a simpledu struct
 * 
 * @param sd: The instance of simpledu
 */
void destroySimpledu(simpledu *sd);

/**
 * @brief: Prints the correct usage of the program
 */
void printUsage();

/**
 * @brief: Helps detect if the string provided is the path
 * 
 * @todo Make sure that the function works with paths with just numbers
 * 
 * @param path: the string to be analyzed
 * 
 * @return: -1 if invalid path, 0 if a file, 1 if a directory and 2 if a symbolic link
 */
int isPath(const char *path);

/**
 * @brief returns the value of the desired depth from the options
 * 
 * @param string: the string to extract the value
 * 
 * @return the value of the depth or -1 if something went wrong 
 */
int getMaxDepth(const char *string);

#endif
