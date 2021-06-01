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

# define HELP	    1
# define VERBOSE	2
# define BAD_OPT    4
# define NO_OPT     8 


typedef struct  s_payload
{
    int     socket;
    int     opt;
    char    *address;


}               t_payload;


/*  FT_PING   */

_Bool       parsing_arguments(int argc, char **argv);
_Bool       check_for_option(char **argv, int8_t id_opt);
_Bool       print_help(void);
_Bool       get_destination(int argc, char **argv, int8_t id, t_payload *payload);
t_payload   *create_payload(void);


/*  LIBFT   */

char	    *ft_strdup(const char *s1);
size_t	    ft_strlen(const char *s);

#endif 
