#ifndef _HANDLER_H_
#define _HANDLER_H_

#include <stdio.h>
#include <ctype.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include "log.h"

/**
 * @brief: Aggregate handler of INTHandler1 and INTHandler2
 * 
 * @param signo: The signal received
 * 
  */
void INTAggregateHandler(int signo);

/**
 * @brief: When the process receives SIGINT the user should confirm if the program should terminate or not (if in fork)
 * 
 * @param signo: The signal received
 * 
  */
void INTHandler1(int signo);

/**
 * @brief: When the process receives SIGINT the user should confirm if the program should terminate or not (if not in fork)
 * 
 * @param signo: The signal received
 * 
  */
void INTHandler2(int signo);

/**
 * @brief: Handles SIGTSTP 
 * 
 * @param signo: The signal received
 * 
  */
void TSTPHandler(int signo);

/**
 * @brief: Handles SIGCONT
 * 
 * @param signo: The signal received
 * 
  */
void CONTHandler(int signo);

#endif
