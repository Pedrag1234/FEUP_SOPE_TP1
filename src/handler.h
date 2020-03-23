#ifndef _HANDLER_H_
#define _HANDLER_H_

#include <stdio.h>
#include <ctype.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>

void INTHandler(int signo);

void TSTPHandler(int signo);

void CONTHandler(int signo);

#endif
