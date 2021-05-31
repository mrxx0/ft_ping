#ifndef FT_PING_H
#define FT_PING_H

#include <sys/socket.h>
#include <sys/types.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>


#define FAILURE -1

#define TRUE 1
#define FALSE 0

#define MALLOC_FAILED NULL

typedef struct  s_payload
{
    int     socket;
    char    pad[4];
    char    *address;

}               t_payload;


_Bool   parsing_arguments(int argc, char **argv);
_Bool   check_for_option(char **argv, int8_t id_opt);
_Bool   print_help(void);
void    get_destination(char **argv, t_payload payload, _Bool shift);




#endif 
