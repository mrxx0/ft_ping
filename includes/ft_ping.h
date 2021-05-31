#ifndef FT_PING_H
#define FT_PING_H

#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

#define FAILURE -1

#define TRUE 1
#define FALSE 0

#define MALLOC_FAILED NULL


_Bool check_for_option(char **argv);
_Bool print_help(void);



#endif 
