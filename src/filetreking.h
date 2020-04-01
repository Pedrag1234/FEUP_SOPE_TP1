#ifndef _FILETREKING_H_
#define _FILETREKING_H_

#include "parser.h"

long folderSize = 0;

/**
 * @brief: prints file path + size in bytes or in blocks according to simpledu args
 * 
 * @param sd: struct containing simpledu definition;
 * @param path: path to the file/directory;
 * @param size: file size;
 * 
 * @return void;
*/
void printFile(simpledu * sd, char * path, long size);

/**
 * @todo: replace instances of exit(1) with exitProcess after importing log.h
 * 
 * @brief: searches for the given file, and then orders its printing
 * 
 * @param sd: struct containing simpledu definition;
 * @param fileName: name of the file to be searched
 * 
 * @return: 1 if failure, 0 if success
*/
int searchFile(simpledu * sd, char * fileName);

/**
 * @todo: replace instances of exit(1) with exitProcess after importing log.h
 * 
 * @brief: search the provided directory in the path and stores the stream in direct
 * 
 * @param path: directory to search
 * 
 * @return: number of directories
*/
int searchDirectory(char * path, char direct[1024][256]);

#endif