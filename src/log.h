#ifndef _LOG_H_
#define _LOG_H_

#include <sys/time.h>

#include <stdlib.h>
#include <stdio.h>

#define DEFAULT "log.txt"

/**
 * @brief: creates a child process and registers its creation on the register log file
 * 
 * @param mainStart: the begining instant main was initiated, used to calculates ms since beginning
 * 
 * @return: void
 * 
 */
void createProcess(struct timeval mainStart);

/**
 * @brief: terminates the current process and registers its creation on the register log file
 * 
 * @param mainStart: the begining instant main was initiated, used to calculates ms since beginning
 * 
 * @return: void
 * 
 */
void exitProcess(struct timeval mainStart);

#endif