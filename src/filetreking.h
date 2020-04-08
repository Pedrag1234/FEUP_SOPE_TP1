#ifndef _FILETREKING_H_
#define _FILETREKING_H_

#include "parser.h"
#include "handler.h"
#include "log.h"

//holds all info related to a certain path
typedef struct pathInfo
{
  struct stat info;
  char path[100];
} pathInfo;

typedef struct container
{
  pathInfo *objects; //array of objects
  int length;        //index aka number of objects
  int size;          //max_size of objects array -> updated if needed
} Container;

/**
 * @brief: prints all files/directories sent to it according to the program flags
 * 
 * @return: none
 * 
*/
void printAll(simpledu *sd, Container *container);

/**
 * @todo: replace instances of exit(1) with exitProcess after importing log.h
 * 
 * @brief: search the provided directory in the path and stores the stream in direct
 * 
 * @param dirPath: path to the file (necessary because of recursion);
 * @param sd: struct containing simpledu definition;
 * @param container: where all directories/files are stored for later printing
 * 
 * @return: number of directories
*/
int searchDirectory(char *dirPath, simpledu *sd, Container *container);

/**
 * @brief: prints file path + size in bytes or in blocks according to simpledu args
 * 
 * @param sd: struct containing simpledu definition;
 * @param path: path to the file;
 * @param size: file size;
 * 
 * @return void;
*/
void printFile(simpledu *sd, char *path, long size);

/**
 * @brief: calculates depth of the given path
 * 
 * @param path: path to calculate depth
 * 
 * @return: calculated depth
*/
int depth(char *path);

#endif