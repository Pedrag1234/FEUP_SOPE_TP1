#ifndef _PIPES_H_
#define _PIPES_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_RESP_SIZE 256

#define WRITE 0
#define READ 1

/**
 * @brief: Executes a command and returns the result to a string
 * 
 * @param cmd: command to be executed
 * @param resp: the return of when the command is executed
 *  
 */
void cmd_2_str(char *cmd, char *resp);

#endif
