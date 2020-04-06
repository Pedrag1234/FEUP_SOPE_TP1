#ifndef _FILETREKING_H_
#define _FILETREKING_H_

#include "parser.h"

void debug(int test);

//holds all info related to a certain path
typedef struct {
    char path[128];
    struct stat info;

}pathInfo;

typedef struct{
    pathInfo * paths;
    int length;
    int size;
}Container;


/**
 * @brief: calculates depth of the given path
 * 
 * @param path: path to calculate depth
 * 
 * @return: calculated depth
*/
unsigned depth(char * path);

/**
 * @brief: prints all files/directories sent to it according to the program flags
 * 
 * @return: none
 * 
*/
void printAll(simpledu * sd, Container * container);

/**
 * @brief: prints file path + size in bytes or in blocks according to simpledu args
 * 
 * @param sd: struct containing simpledu definition;
 * @param path: path to the file;
 * @param size: file size;
 * 
 * @return void;
*/
void printFile(simpledu * sd, char * path, long size);

/**
 * @todo: replace instances of exit(1) with exitProcess after importing log.h
 * 
 * @brief: search the provided directory in the path and stores the stream in direct
 * 
 * @param dirPath: path to the file (necessary because of recursion);
 * @param sd: struct containing simpledu definition;
 * @param folderSize: reference to the var storing the size of the (sub)folders
 * 
 * @return: number of directories
*/
int searchDirectory(char * dirPath, simpledu * sd, Container * container);

#endif