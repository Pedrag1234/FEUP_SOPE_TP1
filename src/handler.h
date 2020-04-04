#ifndef _HANDLER_H_
#define _HANDLER_H_

#include <stdio.h>
#include <ctype.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>

/**
 * @brief: When the process receives SIGINT the user should confirm if the program should terminate or not
 * 
 * @param signo: The signal received
 * 
 * @TODO: add register to logs
  */
void INTHandler(int signo);

/**
 * @brief: Handles SIGTSTP 
 * 
 * @param signo: The signal received
 * 
 * @TODO: add register to logs
  */
void TSTPHandler(int signo);

/**
 * @brief: Handles SIGCONT
 * 
 * @param signo: The signal received
 * 
 * @TODO: add register to logs
  */
void CONTHandler(int signo);

#endif
