#ifndef _LOG_H_
#define _LOG_H_


#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <fcntl.h>

#define DEFAULT "log.txt"

/**
 * @brief: begins time counting and sets up the file
 */
void createFile();

/**
 * @brief: registers creation of a child process on the register log file
 * 
 * @param args: arguments of the command line
 * 
 * @return: void
 */
void createProcess(const char **args);

/**
 * @brief: registers termination of a process by its father process on the register log file
 * 
 * @param status: termination status of the exited process
 * 
 * @return: void
 * 
 */
void exitProcess(int status);

/**
 * @brief: register when a signal is recieved
 * 
 * @param signal: signal recieved
 * 
 * @return: void
*/
void recieveSignal(int signal);

/**
 * @brief: register when a signal is sent
 * 
 * @param signal: signal sent
 * @param pid: destination of sent signal
 * 
 * @return: void
*/
void sendSignal(int signal, pid_t pid);

/**
 * @brief: register when a pipe message is received
 * 
 * @param pipemsg: message received
 * 
 * @return: void
*/
void receivePipe(const char *pipemsg);

/**
 * @brief: register when a pipe message is sent
 * 
 * @param pipemsg: message sent
 * 
 * @return: void
*/
void sendPipe(const char *pipemsg);

/**
 * @brief: register when a folder size is calculated
 * 
 * @param entryRes: Byte/Block size followed by path
 * 
 * @return: void
*/
void entry(const char *entryRes);

/**
 * @brief: closes log file
 */
void CloseFile();



#endif