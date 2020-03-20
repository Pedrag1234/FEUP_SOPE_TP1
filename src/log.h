#ifndef _LOG_H_
#define _LOG_H_

#include <sys/time.h>
#include <sys/types.h>

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> 
#include <string.h> 

#define DEFAULT "log.txt"

void createFile();

/**
 * @brief: creates a child process and registers its creation on the register log file
 * 
 * @param mainStart: the begining instant main was initiated, used to calculates ms since beginning
 * @param pid: process ID of the caller
 * @param args: arguments of the command line
 * 
 * @return: void
 */
void createProcess(struct timeval mainStart, pid_t pid, const char ** args);

/**
 * @brief: terminates the current process and registers its creation on the register log file
 * 
 * @param mainStart: the begining instant main was initiated, used to calculates ms since beginning
 * @param pid: process ID of the caller
 * 
 * @return: void
 * 
 */
void exitProcess(struct timeval mainStart, pid_t pid);

#endif